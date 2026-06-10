#include "simulatorwindow.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDateTime>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSerialPortInfo>
#include <QSpinBox>
#include <QTextEdit>
#include <QTimer>
#include <QVBoxLayout>
#include <QtMath>

static const unsigned char ERROR_NONE = 0x00;
static const unsigned char ERROR_UNKNOWN_OPERATION = 0x01;
static const unsigned char ERROR_CRC = 0x04;

/**
 * @brief SimulatorWindow
 * @author 刘嘉诚
 * @date 2026.06.10
 */
SimulatorWindow::SimulatorWindow(QWidget *parent)
    : QMainWindow(parent),
      serialPort(new QSerialPort(this)),
      measureTimer(new QTimer(this)),
      portComboBox(nullptr),
      scenarioComboBox(nullptr),
      refreshButton(nullptr),
      connectButton(nullptr),
      manualSampleButton(nullptr),
      forwardDoneButton(nullptr),
      reverseDoneButton(nullptr),
      errorButton(nullptr),
      clearLogButton(nullptr),
      autoAckCheckBox(nullptr),
      autoMeasureCheckBox(nullptr),
      sampleCountSpinBox(nullptr),
      statusLabel(nullptr),
      logText(nullptr),
      currentDirectionForward(true),
      samplesRemaining(0),
      sampleIndex(0)
{
    buildUi();
    refreshPorts();
    setConnectedUi(false);

    measureTimer->setInterval(50);
    connect(measureTimer, &QTimer::timeout, this, &SimulatorWindow::sendNextMeasureSample);
    connect(serialPort, &QSerialPort::readyRead, this, &SimulatorWindow::readSerialData);
}

/**
 * @brief ~SimulatorWindow
 * @author 刘嘉诚
 * @date 2026.06.10
 */
SimulatorWindow::~SimulatorWindow()
{
    if(serialPort->isOpen()){
        serialPort->close();
    }
}

/**
 * @brief buildUi
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void SimulatorWindow::buildUi(void)
{
    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    QGroupBox *serialGroup = new QGroupBox("串口连接", central);
    QHBoxLayout *serialLayout = new QHBoxLayout(serialGroup);
    portComboBox = new QComboBox(serialGroup);
    refreshButton = new QPushButton("刷新", serialGroup);
    connectButton = new QPushButton("连接", serialGroup);
    statusLabel = new QLabel("未连接", serialGroup);
    serialLayout->addWidget(new QLabel("COM口", serialGroup));
    serialLayout->addWidget(portComboBox, 1);
    serialLayout->addWidget(refreshButton);
    serialLayout->addWidget(connectButton);
    serialLayout->addWidget(statusLabel);

    QGroupBox *modeGroup = new QGroupBox("模拟选项", central);
    QFormLayout *modeLayout = new QFormLayout(modeGroup);
    scenarioComboBox = new QComboBox(modeGroup);
    scenarioComboBox->addItem("正常数据", Scenario_Normal);
    scenarioComboBox->addItem("零电流", Scenario_ZeroCurrent);
    scenarioComboBox->addItem("欠量程", Scenario_UnderRange);
    scenarioComboBox->addItem("过量程", Scenario_OverRange);
    scenarioComboBox->addItem("波动数据", Scenario_Wave);
    sampleCountSpinBox = new QSpinBox(modeGroup);
    sampleCountSpinBox->setRange(1, 100);
    sampleCountSpinBox->setValue(10);
    autoAckCheckBox = new QCheckBox("自动回复ACK/NACK", modeGroup);
    autoAckCheckBox->setChecked(true);
    autoMeasureCheckBox = new QCheckBox("收到开始测量后自动发送数据", modeGroup);
    autoMeasureCheckBox->setChecked(true);
    modeLayout->addRow("测试场景", scenarioComboBox);
    modeLayout->addRow("每方向数据点数", sampleCountSpinBox);
    modeLayout->addRow(autoAckCheckBox);
    modeLayout->addRow(autoMeasureCheckBox);

    QGroupBox *manualGroup = new QGroupBox("手动发送", central);
    QHBoxLayout *manualLayout = new QHBoxLayout(manualGroup);
    manualSampleButton = new QPushButton("发送一组0x50数据", manualGroup);
    forwardDoneButton = new QPushButton("发送正向完成", manualGroup);
    reverseDoneButton = new QPushButton("发送反向完成", manualGroup);
    errorButton = new QPushButton("发送错误包", manualGroup);
    manualLayout->addWidget(manualSampleButton);
    manualLayout->addWidget(forwardDoneButton);
    manualLayout->addWidget(reverseDoneButton);
    manualLayout->addWidget(errorButton);

    logText = new QTextEdit(central);
    logText->setReadOnly(true);
    clearLogButton = new QPushButton("清空日志", central);

    mainLayout->addWidget(serialGroup);
    mainLayout->addWidget(modeGroup);
    mainLayout->addWidget(manualGroup);
    mainLayout->addWidget(logText, 1);
    mainLayout->addWidget(clearLogButton);

    setCentralWidget(central);
    setWindowTitle("MCU串口模拟器");
    resize(760, 620);

    connect(refreshButton, &QPushButton::clicked, this, &SimulatorWindow::refreshPorts);
    connect(connectButton, &QPushButton::clicked, this, &SimulatorWindow::toggleSerial);
    connect(manualSampleButton, &QPushButton::clicked, this, &SimulatorWindow::sendManualSample);
    connect(forwardDoneButton, &QPushButton::clicked, this, &SimulatorWindow::sendManualForwardDone);
    connect(reverseDoneButton, &QPushButton::clicked, this, &SimulatorWindow::sendManualReverseDone);
    connect(errorButton, &QPushButton::clicked, this, &SimulatorWindow::sendManualError);
    connect(clearLogButton, &QPushButton::clicked, logText, &QTextEdit::clear);
}

/**
 * @brief refreshPorts
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void SimulatorWindow::refreshPorts(void)
{
    QString current = portComboBox->currentText();
    portComboBox->clear();

    const QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &portInfo : ports){
        QString text = portInfo.portName();
        if(!portInfo.description().isEmpty()){
            text += " - " + portInfo.description();
        }
        portComboBox->addItem(text, portInfo.portName());
    }

    int index = portComboBox->findText(current);
    if(index >= 0){
        portComboBox->setCurrentIndex(index);
    }
}

/**
 * @brief toggleSerial
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void SimulatorWindow::toggleSerial(void)
{
    if(serialPort->isOpen()){
        measureTimer->stop();
        serialPort->close();
        rxBuffer.clear();
        setConnectedUi(false);
        appendLog("串口已断开");
        return;
    }

    QString portName = portComboBox->currentData().toString();
    if(portName.isEmpty()){
        appendLog("没有可用串口");
        return;
    }

    serialPort->setPortName(portName);
    serialPort->setBaudRate(QSerialPort::Baud115200);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if(!serialPort->open(QIODevice::ReadWrite)){
        appendLog("打开串口失败: " + serialPort->errorString());
        return;
    }

    setConnectedUi(true);
    appendLog("已连接 " + portName);
}

/**
 * @brief setConnectedUi
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void SimulatorWindow::setConnectedUi(bool connected)
{
    connectButton->setText(connected ? "断开" : "连接");
    statusLabel->setText(connected ? "已连接" : "未连接");
    portComboBox->setEnabled(!connected);
    refreshButton->setEnabled(!connected);
}

/**
 * @brief appendLog
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void SimulatorWindow::appendLog(const QString &text)
{
    QString time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    logText->append(QString("[%1] %2").arg(time).arg(text));
}

/**
 * @brief readSerialData
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void SimulatorWindow::readSerialData(void)
{
    rxBuffer.append(serialPort->readAll());
    parseRxBuffer();
}

/**
 * @brief parseRxBuffer
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void SimulatorWindow::parseRxBuffer(void)
{
    while(rxBuffer.size() >= 3){
        if(static_cast<unsigned char>(rxBuffer.at(0)) != 0xAA ||
           static_cast<unsigned char>(rxBuffer.at(1)) != 0x55){
            rxBuffer.remove(0, 1);
            continue;
        }

        unsigned char bodyLen = static_cast<unsigned char>(rxBuffer.at(2));
        if(bodyLen > 60){
            rxBuffer.remove(0, 1);
            continue;
        }

        int totalLen = 3 + static_cast<int>(bodyLen);
        if(rxBuffer.size() < totalLen){
            return;
        }

        QByteArray packet = rxBuffer.left(totalLen);
        rxBuffer.remove(0, totalLen);

        unsigned short calcCrc = calculateCrc16(packet.left(totalLen - 2));
        unsigned short recvCrc = (static_cast<unsigned char>(packet.at(totalLen - 1)) << 8) |
                                 static_cast<unsigned char>(packet.at(totalLen - 2));

        appendLog("RX " + hexText(packet));
        if(calcCrc != recvCrc){
            appendLog("CRC错误，已发送错误包");
            sendError(ERROR_CRC);
            continue;
        }

        QByteArray payload = packet.mid(3, totalLen - 5);
        handlePayload(payload);
    }
}

/**
 * @brief handlePayload
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void SimulatorWindow::handlePayload(const QByteArray &payload)
{
    if(payload.size() < 2){
        sendError(0x0B);
        return;
    }

    unsigned char ctrlByte = static_cast<unsigned char>(payload.at(0));
    unsigned char seq = static_cast<unsigned char>(payload.at(1));

    appendLog(QString("命令 ctrl=0x%1 seq=%2")
              .arg(ctrlByte, 2, 16, QLatin1Char('0')).toUpper()
              .arg(seq));

    switch(ctrlByte){
    case 0x20:
        if(autoAckCheckBox->isChecked()){
            sendAck(seq, ctrlByte);
            QTimer::singleShot(250, this, [this, seq, ctrlByte](){
                sendOperationDone(seq, ctrlByte, ERROR_NONE);
            });
        }
        break;
    case 0x40:
        if(autoAckCheckBox->isChecked()){
            sendAck(seq, ctrlByte);
        }
        QTimer::singleShot(20, this, &SimulatorWindow::sendReadCurrentOnly);
        break;
    case 0x60:
    case 0x70:
    case 0xA0:
    case 0xC0:
        if(autoAckCheckBox->isChecked()){
            sendAck(seq, ctrlByte);
        }
        break;
    case 0xB0:
        if(autoAckCheckBox->isChecked()){
            sendAck(seq, ctrlByte);
        }
        if(autoMeasureCheckBox->isChecked()){
            bool forward = true;
            if(payload.size() >= 3){
                forward = (static_cast<unsigned char>(payload.at(2)) == 0x00);
            }
            startFakeMeasurement(forward);
        }
        break;
    default:
        if(autoAckCheckBox->isChecked()){
            sendNack(seq, ctrlByte, ERROR_UNKNOWN_OPERATION);
        }
        break;
    }
}

/**
 * @brief startFakeMeasurement
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void SimulatorWindow::startFakeMeasurement(bool forward)
{
    currentDirectionForward = forward;
    samplesRemaining = sampleCountSpinBox->value();
    sampleIndex = 0;
    measureTimer->start();
    appendLog(forward ? "开始模拟正向测量" : "开始模拟反向测量");
}

/**
 * @brief sendNextMeasureSample
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void SimulatorWindow::sendNextMeasureSample(void)
{
    if(samplesRemaining <= 0){
        measureTimer->stop();
        sendMeasureComplete(currentDirectionForward);
        return;
    }

    sendVoltageCurrentSample();
    sampleIndex++;
    samplesRemaining--;
}

/**
 * @brief sendManualSample
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void SimulatorWindow::sendManualSample(void)
{
    sendVoltageCurrentSample();
}

/**
 * @brief sendManualForwardDone
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void SimulatorWindow::sendManualForwardDone(void)
{
    sendMeasureComplete(true);
}

/**
 * @brief sendManualReverseDone
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void SimulatorWindow::sendManualReverseDone(void)
{
    sendMeasureComplete(false);
}

/**
 * @brief sendManualError
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void SimulatorWindow::sendManualError(void)
{
    sendError(ERROR_UNKNOWN_OPERATION);
}

/**
 * @brief sendFrame
 * @author 刘嘉诚
 * @date 2026.06.10
 */
bool SimulatorWindow::sendFrame(const QByteArray &payload)
{
    if(!serialPort->isOpen()){
        appendLog("串口未连接，发送失败");
        return false;
    }

    QByteArray packet;
    packet.append(static_cast<char>(0xAA));
    packet.append(static_cast<char>(0x55));
    packet.append(static_cast<char>(payload.size() + 2));
    packet.append(payload);

    unsigned short crc = calculateCrc16(packet);
    packet.append(static_cast<char>(crc & 0xFF));
    packet.append(static_cast<char>((crc >> 8) & 0xFF));

    qint64 written = serialPort->write(packet);
    if(written < 0){
        appendLog("发送失败: " + serialPort->errorString());
        return false;
    }

    appendLog("TX " + hexText(packet));
    return true;
}

/**
 * @brief sendAck
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void SimulatorWindow::sendAck(unsigned char seq, unsigned char originCtrlByte)
{
    QByteArray payload;
    payload.append(static_cast<char>(0x10));
    payload.append(static_cast<char>(seq));
    payload.append(static_cast<char>(originCtrlByte));
    payload.append(static_cast<char>(0x00));
    payload.append(static_cast<char>(ERROR_NONE));
    sendFrame(payload);
}

/**
 * @brief sendNack
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void SimulatorWindow::sendNack(unsigned char seq, unsigned char originCtrlByte, unsigned char errorNumber)
{
    QByteArray payload;
    payload.append(static_cast<char>(0x10));
    payload.append(static_cast<char>(seq));
    payload.append(static_cast<char>(originCtrlByte));
    payload.append(static_cast<char>(0x01));
    payload.append(static_cast<char>(errorNumber));
    sendFrame(payload);
}

/**
 * @brief sendOperationDone
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void SimulatorWindow::sendOperationDone(unsigned char seq, unsigned char originCtrlByte, unsigned char errorNumber)
{
    QByteArray payload;
    payload.append(static_cast<char>(0x30));
    payload.append(static_cast<char>(seq));
    payload.append(static_cast<char>(originCtrlByte));
    payload.append(static_cast<char>(errorNumber == ERROR_NONE ? 0x00 : 0x01));
    payload.append(static_cast<char>(errorNumber));
    sendFrame(payload);
}

/**
 * @brief sendError
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void SimulatorWindow::sendError(unsigned char errorNumber)
{
    QByteArray payload;
    payload.append(static_cast<char>(0xF0));
    payload.append(static_cast<char>(errorNumber));
    sendFrame(payload);
}

/**
 * @brief sendReadCurrentOnly
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void SimulatorWindow::sendReadCurrentOnly(void)
{
    QByteArray payload;
    payload.append(static_cast<char>(0x40));
    payload.append(fakeAdcBytes(false));
    sendFrame(payload);
}

/**
 * @brief sendVoltageCurrentSample
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void SimulatorWindow::sendVoltageCurrentSample(void)
{
    QByteArray payload;
    payload.append(static_cast<char>(0x50));
    payload.append(fakeAdcBytes(true));
    payload.append(fakeAdcBytes(false));
    sendFrame(payload);
}

/**
 * @brief sendMeasureComplete
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void SimulatorWindow::sendMeasureComplete(bool forward)
{
    QByteArray payload;
    payload.append(static_cast<char>(0xB0));
    payload.append(static_cast<char>(forward ? 0x55 : 0xAA));
    sendFrame(payload);
    appendLog(forward ? "已发送正向完成" : "已发送反向完成");
}

/**
 * @brief fakeAdcBytes
 * @author 刘嘉诚
 * @date 2026.06.10
 */
QByteArray SimulatorWindow::fakeAdcBytes(bool voltageChannel) const
{
    Scenario scenario = static_cast<Scenario>(scenarioComboBox->currentData().toInt());
    double ratio = 0.5;

    switch(scenario){
    case Scenario_Normal:
        ratio = voltageChannel ? 0.32 : 0.50;
        break;
    case Scenario_ZeroCurrent:
        ratio = voltageChannel ? 0.32 : 0.0;
        break;
    case Scenario_UnderRange:
        ratio = voltageChannel ? 0.02 : 0.50;
        break;
    case Scenario_OverRange:
        ratio = voltageChannel ? 0.96 : 0.50;
        break;
    case Scenario_Wave:
        ratio = voltageChannel
                ? 0.32 + 0.05 * qSin(sampleIndex / 3.0)
                : 0.50 + 0.03 * qCos(sampleIndex / 4.0);
        break;
    }

    if(ratio < 0.0){
        ratio = 0.0;
    }
    if(ratio > 1.0){
        ratio = 1.0;
    }
    return adcBytesFromRatio(ratio);
}

/**
 * @brief adcBytesFromRatio
 * @author 刘嘉诚
 * @date 2026.06.10
 */
QByteArray SimulatorWindow::adcBytesFromRatio(double ratio) const
{
    quint32 code = static_cast<quint32>(ratio * 0x7FFFFF);
    QByteArray bytes;
    bytes.append(static_cast<char>((code >> 16) & 0xFF));
    bytes.append(static_cast<char>((code >> 8) & 0xFF));
    bytes.append(static_cast<char>(code & 0xFF));
    return bytes;
}

/**
 * @brief calculateCrc16
 * @author 刘嘉诚
 * @date 2026.06.10
 */
unsigned short SimulatorWindow::calculateCrc16(const QByteArray &data) const
{
    unsigned int crc = 0xFFFF;
    unsigned int poly = 0xA001;

    for(int i = 0; i < data.size(); ++i){
        unsigned char byte = static_cast<unsigned char>(data.at(i));
        crc ^= byte;
        for(int j = 0; j < 8; ++j){
            if(crc & 0x0001){
                crc >>= 1;
                crc ^= poly;
            }else{
                crc >>= 1;
            }
        }
        crc &= 0xFFFF;
    }

    return static_cast<unsigned short>(crc);
}

/**
 * @brief hexText
 * @author 刘嘉诚
 * @date 2026.06.10
 */
QString SimulatorWindow::hexText(const QByteArray &data) const
{
    return QString(data.toHex(' ').toUpper());
}
