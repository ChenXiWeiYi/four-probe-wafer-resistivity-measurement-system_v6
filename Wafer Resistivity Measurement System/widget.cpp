#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QSerialPortInfo>
#include <QDataStream>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , serialPort(new QSerialPort(this))
    , SelCOMAction(nullptr)
    , SelChannel(0)
    , responseTimer(new QTimer(this))
    , Timer_MeasureInterval(new QTimer(this))
    , Timer_EchoMonitor(new QTimer(this))
    , Timer_ContactMonitor(new QTimer(this))
    , Timer_COMScan(new QTimer(this))
    , Timer_Heartbeat(new QTimer(this))
    , ChannelSwitchSuccessFlag(false)
{
    // 初始化UI
    ui->setupUi(this);
    connect(ui->Button_MeasStart, &QPushButton::clicked, this, &Widget::onButtonMeasStartClicked);
    connect(ui->Button_SendControlVoltage, &QPushButton::clicked, this, &Widget::onButtonSendControlVoltageClicked);
    connect(ui->Button_ControlVoltage, &QPushButton::clicked, this, &Widget::onButtonControlVoltageClicked);
    connect(ui->Button_SendCurrentPosition, &QPushButton::clicked, this, &Widget::onButtonSendCurrentPositionClicked);
    connect(ui->Button_SendVoltageRange, &QPushButton::clicked, this, &Widget::onButtonSendVoltageRangeClicked);
    connect(ui->Button_SelSemiType, &QPushButton::clicked, this, &Widget::onButtonSelSemiTypeClicked);

    connect(ui->cin_Temperature, &QLineEdit::editingFinished, this, &Widget::onButtonTemperatureClicked);
    connect(ui->cin_Thickness, &QLineEdit::editingFinished, this, &Widget::onButtonThicknessClicked);
    connect(ui->cin_SampleDiameter, &QLineEdit::editingFinished, this, &Widget::onButtonSampleDiameterClicked);
    connect(ui->cin_ProbeSpacing, &QLineEdit::editingFinished, this, &Widget::onButtonProbeSpacingClicked);
    connect(ui->cin_FspCorrectionFactor, &QLineEdit::editingFinished, this, &Widget::onButtonFspCorrectionFactorClicked);
    connect(ui->cin_a, &QLineEdit::editingFinished, this, &Widget::onButtonabClicked);
    connect(ui->cin_b, &QLineEdit::editingFinished, this, &Widget::onButtonabClicked);
    connect(ui->cin_CurrErrorBound, &QLineEdit::editingFinished, this, &Widget::onButtonCurrErrorBoundClicked);
    connect(ui->cin_Kp, &QLineEdit::editingFinished, this, &Widget::Slot_cin_Kp);
    connect(ui->cin_Ti, &QLineEdit::editingFinished, this, &Widget::Slot_cin_Ti);
    connect(ui->cin_Td, &QLineEdit::editingFinished, this, &Widget::Slot_cin_Td);
//    connect(ui->Button_Temperature, &QPushButton::clicked, this, &Widget::onButtonTemperatureClicked);
//    connect(ui->Button_Thickness, &QPushButton::clicked, this, &Widget::onButtonThicknessClicked);
//    connect(ui->Button_SampleDiameter, &QPushButton::clicked, this, &Widget::onButtonSampleDiameterClicked);
//    connect(ui->Button_ProbeSpacing, &QPushButton::clicked, this, &Widget::onButtonProbeSpacingClicked);
//    connect(ui->Button_FspCorrectionFactor, &QPushButton::clicked, this, &Widget::onButtonFspCorrectionFactorClicked);
//    connect(ui->Button_ab, &QPushButton::clicked, this, &Widget::onButtonabClicked);
//    connect(ui->Button_CurrErrorBound, &QPushButton::clicked, this, &Widget::onButtonCurrErrorBoundClicked);


    /** 窗口基础设置 */
    setWindowTitle("四探针测电阻率系统");

    /***************初始化菜单***************/
    Init_Menu();

    /***************初始化串口***************/
    /* 2025.10.25 */
    // 注意：这里不再包含串口的具体配置和连接，这些移到 widget_serial.cpp
    // serialPort = new QSerialPort(this);
    // ... 配置串口 ...
    connect(serialPort, &QSerialPort::readyRead, this, &Widget::readSerialData);
    connect(serialPort,
            static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::errorOccurred),
            this,
            &Widget::onSerialPortError);
    serialPort->setBaudRate(QSerialPort::Baud115200);
    // 关联其他按钮信号槽
    connect(ui->Button_logText1_CLR, &QPushButton::clicked, [this](){ ui->logText_1->clear(); });

    // 定时器关联
    connect(Timer_MeasureInterval, &QTimer::timeout,this,&Widget::onTimerMeasureIntervalTimeout);
    Timer_MeasureInterval->setSingleShot(true);
    connect(Timer_EchoMonitor, &QTimer::timeout, this, &Widget::onTimerEchoMonitorTimeout);
    Timer_EchoMonitor->setSingleShot(true);
    connect(Timer_ContactMonitor, &QTimer::timeout, this, &Widget::onTimerContactMonitorTimeout);
    Timer_ContactMonitor->setSingleShot(true);
    connect(Timer_COMScan, &QTimer::timeout, this, &Widget::onTimerCOMScanTimeout);
    Timer_COMScan->setSingleShot(false);
    connect(Timer_Heartbeat, &QTimer::timeout, this, &Widget::onTimerHeartbeatTimeout);
    Timer_Heartbeat->setSingleShot(false);
    Start_AutoConnectSerial();


    //
    ui->TableWidget_f->setRowCount(500);
    ui->TableWidget_f->setColumnCount(10);
    ui->TableWidget_f->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i = 0; i <= 9; i++){
        ui->TableWidget_f->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::number(i+1)));
    }
    ui->TableWidget_r->setRowCount(500);
    ui->TableWidget_r->setColumnCount(10);
    ui->TableWidget_r->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i = 0; i <= 9; i++){
        ui->TableWidget_r->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::number(i+1)));
    }
    /***************初始化进度条***************/
    Init_Param_Channel();
    ui->ProgressBar_Init->setValue(14);
    Init_Param_ab();
    ui->ProgressBar_Init->setValue(28);
    Init_Param_Temperature();
    ui->ProgressBar_Init->setValue(42);
    Init_Param_Thickness();
    ui->ProgressBar_Init->setValue(56);
    Init_Param_ProbeSpacing();
    ui->ProgressBar_Init->setValue(70);
    Init_Param_SampleDiameter();
    ui->ProgressBar_Init->setValue(84);
    Init_Param_CurrErrorBound();
    ui->ProgressBar_Init->setValue(90);
    Init_Param_SemiType();
    ui->ProgressBar_Init->setValue(95);
    Init_Param_FspCorrectionFactor();
    ui->ProgressBar_Init->setValue(98);
    Init_Param_ControlVoltages();
    ui->ProgressBar_Init->setValue(99);
    Init_Param_PIDParameters();
    Init_Param_PIDControlEnabled();
    ui->ProgressBar_Init->setValue(100);

    ui->ProgressBar_MeasureProgress->setValue(0);

    initLineEditPlaceholder(ui->cin_a, "输入a");
    initLineEditPlaceholder(ui->cin_b, "输入b");
    initLineEditPlaceholder(ui->cin_Temperature, "输入温度");
    initLineEditPlaceholder(ui->cin_CurrErrorBound, "输入阈值");
    initLineEditPlaceholder(ui->cin_Thickness, "输入厚度");
    initLineEditPlaceholder(ui->cin_ProbeSpacing, "输入探针间距");
    initLineEditPlaceholder(ui->cin_SampleDiameter, "输入样品直径");
    initLineEditPlaceholder(ui->cin_FspCorrectionFactor, "输入探针修正系数");

    Init_Style_Button();
}

/******************************主函数结束******************************/

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    MeasureState_used.Flag_FirstReadCurrent = true;
    Timer_ContactMonitor->start(200);   // 200ms轮询
    MeasureState_used.Flag_TestCurrent = true;
    MeasureState_used.Time_MeasurementStart = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
}

void Widget::on_pushButton_2_clicked()
{
    MeasureState_used.Flag_TestCurrent = false;
}

void Widget::on_pushButton_3_clicked()
{
    int mcuCurrPos = CurrentMcuCurrPos();
    Controller_used.PV_Current = 0;
    Controller_used.SP_Current = Map_CurrValue.value(static_cast<CurrPos_TypeDef>(mcuCurrPos));
    Controller_used.Last_uk = Param_used.ControlVoltages[static_cast<int>(Param_used.CurrPos)];
    Controller_used.Last_Err = 0.0;      // 上次误差 (用于微分)
    MeasureState_used.cnt_Curr = 0;
    ui->logText_1->append("清理成功");
}
