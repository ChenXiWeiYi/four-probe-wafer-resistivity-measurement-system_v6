#include "widget.h"
#include "ui_widget.h"
#include <QSerialPortInfo>

static const int COM_SCAN_DISCONNECTED_INTERVAL_MS = 1000;
static const int COM_SCAN_CONNECTED_INTERVAL_MS = 2000;
static const int HEARTBEAT_INTERVAL_MS = 5000;

/**
 * @brief Widget::Start_AutoConnectSerial 启动串口自动连接扫描
 * @author 刘嘉诚
 * @date 2026.06.04
 */
void Widget::Start_AutoConnectSerial(void)
{
    Timer_COMScan->start(COM_SCAN_DISCONNECTED_INTERVAL_MS);
    Timer_Heartbeat->setInterval(HEARTBEAT_INTERVAL_MS);
    onTimerCOMScanTimeout();
}

/**
 * @brief Widget::Is_CH340Port 判断串口是否为CH340C候选端口
 * @param portInfo 串口信息
 * @return 是否为CH340C候选端口
 * @author 刘嘉诚
 * @date 2026.06.04
 */
bool Widget::Is_CH340Port(const QSerialPortInfo &portInfo) const
{
    bool matchID = false;
    bool matchDescription = false;

    if(portInfo.hasVendorIdentifier() && portInfo.hasProductIdentifier()){
        matchID = (portInfo.vendorIdentifier() == 0x1A86 &&
                   portInfo.productIdentifier() == 0x7523);
    }

    matchDescription = portInfo.description().contains("CH340", Qt::CaseInsensitive);

    return matchID || matchDescription;
}

/**
 * @brief Widget::onTimerCOMScanTimeout 扫描CH340C热插拔状态
 * @author 刘嘉诚
 * @date 2026.06.04
 */
void Widget::onTimerCOMScanTimeout(void)
{
    const QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    if(CommStruct_used.Flag_isSerialConnected || CommStruct_used.Flag_isSerialProbing || serialPort->isOpen()){
        bool currentPortExists = false;
        QString currentPortName = serialPort->portName();

        for(const QSerialPortInfo &portInfo : ports){
            if(portInfo.portName() == currentPortName){
                currentPortExists = true;
                break;
            }
        }

        if(!currentPortExists){
            Handle_SerialDisconnected("通信连接中断，串口设备已移除", true);
        }
        return;
    }

    for(const QSerialPortInfo &portInfo : ports){
        if(Is_CH340Port(portInfo)){
            Open_SerialPortByName(portInfo.portName(), true);
            return;
        }
    }
}

/**
 * @brief Widget::Open_SerialPortByName 打开串口
 * @param portName 串口名
 * @param autoConnect 是否为自动连接探测
 * @return 是否成功打开串口并发起后续流程
 * @author 刘嘉诚
 * @date 2026.06.04
 */
bool Widget::Open_SerialPortByName(const QString &portName, bool autoConnect)
{
    Timer_Heartbeat->stop();
    Timer_EchoMonitor->stop();

    CommStruct_used.Flag_isWaitingEcho = false;
    CommStruct_used.Flag_isWaitingDone = false;
    CommStruct_used.Flag_isEchoVerified = false;
    CommStruct_used.Flag_isSerialConnected = false;
    CommStruct_used.Flag_isSerialProbing = false;
    CommStruct_used.Cnt_HeartbeatLost = 0;
    m_buffer.clear();

    if(serialPort->isOpen()){
        serialPort->close();
    }

    serialPort->setPortName(portName);
    serialPort->setBaudRate(QSerialPort::Baud115200);

    if(!serialPort->open(QIODevice::ReadWrite)){
        ui->logText_1->append(QString("错误: 无法打开 %1 - %2").arg(portName).arg(serialPort->errorString()));
        ui->Button_SelCOM->setText("---");
        SyncUserStatusLabels();
        return false;
    }

    ui->Button_SelCOM->setText(portName);
    SetOptionalLabelText("lblConnectStatus", "连接中");

    if(autoConnect){
        CommStruct_used.Flag_isSerialProbing = true;
        ui->logText_1->append(QString("发现CH340C候选串口: %1, 正在确认设备").arg(portName));
        Command_Heartbeat();

        if(!CommStruct_used.Flag_isWaitingEcho){
            Handle_SerialDisconnected("设备识别帧发送失败", false);
            return false;
        }
    }else{
        Handle_SerialConnected(portName, false);
        Command_SendPIDControlConfig();
    }

    return true;
}

/**
 * @brief Widget::Handle_SerialConnected 标记串口已连接
 * @param portName 串口名
 * @param autoConnect 是否为自动连接成功
 * @author 刘嘉诚
 * @date 2026.06.04
 */
void Widget::Handle_SerialConnected(const QString &portName, bool autoConnect)
{
    CommStruct_used.Flag_isSerialConnected = true;
    CommStruct_used.Flag_isSerialProbing = false;
    CommStruct_used.Cnt_HeartbeatLost = 0;

    ui->Button_SelCOM->setText(portName);
    if(autoConnect){
        ui->logText_1->append(QString("自动连接成功: %1").arg(portName));
    }else{
        ui->logText_1->append(QString("成功: 打开 %1").arg(portName));
    }

    Timer_COMScan->start(COM_SCAN_CONNECTED_INTERVAL_MS);
    Timer_Heartbeat->start(HEARTBEAT_INTERVAL_MS);
    SyncUserStatusLabels();
}

/**
 * @brief Widget::Handle_SerialDisconnected 处理串口断开
 * @param reason 断开原因
 * @param showPopup 是否弹窗提示
 * @author 刘嘉诚
 * @date 2026.06.04
 */
void Widget::Handle_SerialDisconnected(const QString &reason, bool showPopup)
{
    bool wasActive = CommStruct_used.Flag_isSerialConnected ||
                     CommStruct_used.Flag_isSerialProbing ||
                     serialPort->isOpen();

    Timer_Heartbeat->stop();
    Timer_EchoMonitor->stop();

    CommStruct_used.Flag_isWaitingEcho = false;
    CommStruct_used.Flag_isWaitingDone = false;
    CommStruct_used.Flag_isEchoVerified = false;
    CommStruct_used.Flag_isSerialConnected = false;
    CommStruct_used.Flag_isSerialProbing = false;
    CommStruct_used.Cnt_HeartbeatLost = 0;
    m_buffer.clear();

    if(serialPort->isOpen()){
        serialPort->close();
    }

    ui->Button_SelCOM->setText("---");
    Timer_COMScan->start(COM_SCAN_DISCONNECTED_INTERVAL_MS);
    SyncUserStatusLabels();

    if(wasActive){
        ui->logText_1->append(reason);
        if(showPopup){
            Popup_Window("错误", reason);
        }
    }
}

/**
 * @brief Widget::onTimerHeartbeatTimeout 空闲时发送通信心跳
 * @author 刘嘉诚
 * @date 2026.06.04
 */
void Widget::onTimerHeartbeatTimeout(void)
{
    if(!CommStruct_used.Flag_isSerialConnected || !serialPort->isOpen()){
        return;
    }

    if(CommStruct_used.Flag_isWaitingEcho || CommStruct_used.Flag_isWaitingDone){
        return;
    }

    Command_Heartbeat();
}

/**
 * @brief Widget::onSerialPortError 处理串口错误
 * @param error 串口错误类型
 * @author 刘嘉诚
 * @date 2026.06.04
 */
void Widget::onSerialPortError(QSerialPort::SerialPortError error)
{
    if(error == QSerialPort::NoError){
        return;
    }

    if(error == QSerialPort::ResourceError || error == QSerialPort::DeviceNotFoundError){
        Handle_SerialDisconnected("通信连接中断，串口设备已断开", true);
    }
}
