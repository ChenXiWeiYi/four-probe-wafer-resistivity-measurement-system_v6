#include "widget.h"
#include <QDebug>

void Widget::ControlLoop_Update(double PV_Current)
{
    if(!Param_used.PIDControlEnabled){
        return;
    }

    double err = Controller_used.SP_Current - PV_Current;
    double output_voltage = 2.5;

    double RE = err / Controller_used.SP_Current * 100;
    ui->Label_RE_Current->setText(QString::number(RE));
    AppendValueToFile(Controller_used.SP_Current, VALUE_RESISTANCE);
    AppendValueToFile(PV_Current, VALUE_RESISTANCE);
    AppendValueToFile(err, VALUE_Err);
    AppendValueToFile(RE, VALUE_RESISTANCE);
    AppendValueToFile(Controller_used.SP_Current, VALUE_SP_Current);

    double P = Controller_used.Kp * (err - Controller_used.Last_Err);
    double Ki = Controller_used.Kp / Controller_used.Ti;
    double I = Ki * err;
    double Kd = Controller_used.Kp * Controller_used.Td;
    double D = Kd * (err + Controller_used.Last_last_Err - 2 * Controller_used.Last_Err);

    output_voltage = Controller_used.Last_uk + P + I + D;

    AppendValueToFile(P + I + D, VALUE_delta_uk);
    AppendValueToFile(Controller_used.Last_uk, VALUE_Last_uk);
    AppendValueToFile(output_voltage, VALUE_uk);
    AppendValueToFile(err, VALUE_Err);

    Controller_used.Last_uk = output_voltage;
    Controller_used.Last_last_Err = Controller_used.Last_Err;
    Controller_used.Last_Err = err;

    qDebug() << "PID control";
    Command_SendCustomControlVoltage(static_cast<float>(output_voltage));
}
