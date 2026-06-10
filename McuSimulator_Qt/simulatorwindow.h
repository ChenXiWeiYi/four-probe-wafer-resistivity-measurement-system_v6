#ifndef SIMULATORWINDOW_H
#define SIMULATORWINDOW_H

#include <QByteArray>
#include <QMainWindow>
#include <QSerialPort>

class QCheckBox;
class QComboBox;
class QLabel;
class QPushButton;
class QSpinBox;
class QTextEdit;
class QTimer;

class SimulatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimulatorWindow(QWidget *parent = nullptr);
    ~SimulatorWindow();

private slots:
    void refreshPorts(void);
    void toggleSerial(void);
    void readSerialData(void);
    void sendManualSample(void);
    void sendManualForwardDone(void);
    void sendManualReverseDone(void);
    void sendManualError(void);
    void sendNextMeasureSample(void);

private:
    enum Scenario
    {
        Scenario_Normal = 0,
        Scenario_ZeroCurrent,
        Scenario_UnderRange,
        Scenario_OverRange,
        Scenario_Wave
    };

    QSerialPort *serialPort;
    QByteArray rxBuffer;
    QTimer *measureTimer;

    QComboBox *portComboBox;
    QComboBox *scenarioComboBox;
    QPushButton *refreshButton;
    QPushButton *connectButton;
    QPushButton *manualSampleButton;
    QPushButton *forwardDoneButton;
    QPushButton *reverseDoneButton;
    QPushButton *errorButton;
    QPushButton *clearLogButton;
    QCheckBox *autoAckCheckBox;
    QCheckBox *autoMeasureCheckBox;
    QSpinBox *sampleCountSpinBox;
    QLabel *statusLabel;
    QTextEdit *logText;

    bool currentDirectionForward;
    int samplesRemaining;
    int sampleIndex;

    void buildUi(void);
    void setConnectedUi(bool connected);
    void appendLog(const QString &text);

    void parseRxBuffer(void);
    void handlePayload(const QByteArray &payload);

    bool sendFrame(const QByteArray &payload);
    void sendAck(unsigned char seq, unsigned char originCtrlByte);
    void sendNack(unsigned char seq, unsigned char originCtrlByte, unsigned char errorNumber);
    void sendOperationDone(unsigned char seq, unsigned char originCtrlByte, unsigned char errorNumber);
    void sendError(unsigned char errorNumber);
    void sendReadCurrentOnly(void);
    void sendVoltageCurrentSample(void);
    void sendMeasureComplete(bool forward);

    void startFakeMeasurement(bool forward);
    QByteArray fakeAdcBytes(bool voltageChannel) const;
    QByteArray adcBytesFromRatio(double ratio) const;
    unsigned short calculateCrc16(const QByteArray &data) const;
    QString hexText(const QByteArray &data) const;
};

#endif // SIMULATORWINDOW_H
