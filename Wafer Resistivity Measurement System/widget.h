#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "global_struct_define.h"
#include <QSerialPort>
#include <QTimer>
#include "ui_widget.h"
#include <QVector>
#include "global_maps.h"

class Widget : public QWidget
{
    Q_OBJECT
protected:
    void keyPressEvent(QKeyEvent *event) override;

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    /******************* widget_slots.cpp *******************/
    void onButtonMeasStartClicked();
    void onButtonSendControlVoltageClicked();
    void onButtonSendCurrentPositionClicked();
    void onButtonSendVoltageRangeClicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Widget *ui;                    // UI指针，用于访问UI控件
    ParamStruct_TypeDef Param_used;
    MeasureStateStruct_TypeDef MeasureState_used;
    CommStruct_TypeDef CommStruct_used;
    QVector<MeasureValueStruct_TypeDef> Buffer_MeasureValue_f;
    QVector<MeasureValueStruct_TypeDef> Buffer_MeasureValue_r;
    // 菜单和串口相关成员
    QMenu *Menu_CurrPos;                // 电流档位选择菜单
    QMenu *Menu_VolRange;
    QMenu *Menu_COM;                    // COM口选择菜单
    QMenu *Menu_MeasureMode;
    QSerialPort *serialPort;           // 串口对象
    QAction *SelCOMAction;             // 当前选中的COM口
    int SelChannel;                    // 当前选中的通道号
    QTimer *responseTimer;             // 检查通道切换响应的定时器
    QTimer *Timer_MeasureInterval;
    QTimer *Timer_EchoMonitor;
    QTimer *Timer_ContactMonitor;
    bool ChannelSwitchSuccessFlag;     // 通道切换成功标志位
    QVector<double> ResistivityValue_QVector;
    QByteArray m_buffer; // 全局数据缓存区
    ControllerStruct_TypeDef Controller_used;   // 控制器全局变量



    // ============================= 参数 ============================ //
    /************************* param_init.cpp ************************/
    void Init_Param_ab(void);
    void Init_Param_Channel(void);
    void Init_Param_Temperature(void);
    void Init_Param_Thickness(void);
    void Init_Param_ProbeSpacing(void);
    void Init_Param_SampleDiameter(void);
    void Init_Param_CurrErrorBound(void);
    void Init_Param_FspCorrectionFactor(void);
    void Init_Param_SemiType(void);
    void Init_Param_ControlVoltages(void);
    void Init_Param_PIDParameters(void);
    void Init_Param_PIDControlEnabled(void);
    /************************ param_common.cpp ***********************/
    QVariant Param_Setting_Read(ParamName_TypeDef ParamName);
    bool Param_Setting_Write(ParamName_TypeDef ParamName, const QString &ParamValue);
    bool Param_Setting_Write(ParamName_TypeDef ParamName, int ParamValue);
    bool Param_Setting_Write(ParamName_TypeDef ParamName, float ParamValue);
    bool Param_Setting_Write(ParamName_TypeDef ParamName, double ParamValue);
    QString VectorToString(const QVector<float> &vec);
    QString VectorToString(const QVector<double> &vec);
    QVariant Return_Param_used(ParamName_TypeDef ParamName);
    void Modify_Param_used(ParamName_TypeDef ParamName, double value);
    void Modify_Param_used(ParamName_TypeDef ParamName, int value);
    int CurrentMcuCurrPos(void) const;
    int CurrentPidParamIndex(void) const;
    void Load_PIDParamsForCurrentPosition(void);
    /********************** param_correction.cpp *********************/
    void Update_GeometryCorrectionFactor(void);
    void Update_CorrectionFactor(double Resistance);
    double LinearInterpolate(const QMap<double, double>& map, double inputX);
    /********************* param_slots_channel.cpp *******************/
    void onMenuCurrPosTriggered(QAction *action);
    void onMenuVolRangeTriggered(QAction *action);
    void onMenuCOMTriggered(QAction *action);
    void onMenuMeasureModeTriggered(QAction *action);
    /************************ param_slots.cpp ************************/
    void onButtonSelSemiTypeClicked();
    void onButtonSemiTypeClicked();
    void onButtonCurrErrorBoundClicked();
    void onButtonabClicked();
    void onButtonTemperatureClicked();
    void onButtonThicknessClicked();
    void onButtonProbeSpacingClicked();
    void onButtonSampleDiameterClicked();
    void onButtonFspCorrectionFactorClicked();
    void onButtonControlVoltageClicked();

    // ============================= 测量 ============================ //
    /*********************** measure_start.cpp ***********************/
    void Measure_Start(void);
    /********************* measure_paramcheck.cpp ********************/
    bool Measure_CheckParam(void);
    /********************** measure_complete.cpp *********************/
    void Measure_Complete(void);
    void Measure_Complete_MODE_SINGLE(void);
    void Measure_Complete_MODE_10TIMES_SINGLEPOINT_AUTO(void);
    void Measure_Complete_MODE_10TIMES_SINGLEPOINT_MAN(void);
    /*********************** measure_display.cpp *********************/
    void Add_Resistivity2Table(double value);
    /********************** measure_warning.cpp **********************/
    void Measure_Warning(void);
    /*********************** measure_timer.cpp ***********************/
    void onTimerContactMonitorTimeout();
    void onTimerMeasureIntervalTimeout();


    // ============================ 数据处理 ========================== //
    /********************** dateprocess_gain.cpp *********************/
    double Return_DataGain(ValueType_TypeDef ValueType);
    /******************** dateprocess_adc.cpp *******************/
    double DataProcess_ADC1_Voltage(const QByteArray &rawData_3Byte);
    double DataProcess_ADC2_Current(const QByteArray &rawData_3Byte);
    /********************** dateprocess_save.cpp *********************/
    void Process_Resistivity(double Voltage, double Current);
    void AppendValueToFile(double Value, ValueType_TypeDef ValueType);

    // ============================= 通信 ============================ //
    /********************** serial_answer.cpp ************************/
    void DispatchPacket(const QByteArray &payload);
    void Answer_CurrentPosition(void);
    void Answer_VoltageRange(void);
    void Answer_ModifyControlVoltage(void);
    void Answer_VoltageCurrentRecieve(const QByteArray &payload);
    void Answer_MeasureState(const QByteArray &payload);
    void Answer_ErrorRecieve(const QByteArray &payload);
    void Answer_ReadCurrentOnly(const QByteArray &payload);
    void Answer_CurrentForControl(const QByteArray &payload);
    /********************** serial_command.cpp ***********************/
    void Command_SwitchCurrPos(void);
    void Command_SwitchVolRange(void);
    void Command_ModifyControlVoltage(void);
    void Command_StartMeasurement(void);
    void Command_ReadCurrentOnly(void);
    void Command_SendPIDControlConfig(void);
    void Command_SendCustomControlVoltage(float voltage);
    /****************** serial_calculate_crc16.cpp *******************/
    unsigned short Calculate_CRC16(const QByteArray &data);
    /****************** serial_readserialdata.cpp ********************/
    void readSerialData(void);
    /**************** serial_protocol_sendpacket.cpp *****************/
    void Protocol_SendPacket(const QByteArray &payload);
    /****************** serial_send_contrlbyte.cpp *******************/
    void Send_ControlByte(char CtrlByte);
    /********************* serial_echoerror.cpp **********************/
    void onTimerEchoMonitorTimeout(void);

    /*********************** controlloop.cpp *************************/
    void ControlLoop_Update(double PV_Current);


    /*********************** widget_common.cpp ***********************/
    void Popup_Window(QString title, QString content);
    bool Popup_Confirm_Dialog(const QString &windowTitle, const QString &content);
    void initLineEditPlaceholder(QLineEdit *lineEdit, const QString &placeholderText);
    void AppendTimeToFile(const QString& FileName);

    /********************** widget_ui_design.cpp *********************/
    void Init_Style_Button(void);
    void SetStyle_PushButton(QPushButton *btn);
    void SetStyle_ToolButton(QToolButton *btn);

    /************************ menu_init.cpp **************************/
    void Init_Menu(void);
    void Init_Menu_CurrPos(void);
    void Init_Menu_VolRange(void);
    void Init_Menu_MeasureMode(void);
    void Init_Menu_COM(void);

    void Slot_cin_Kp(void);
    void Slot_cin_Ti(void);
    void Slot_cin_Td(void);

};

#endif // WIDGET_H
