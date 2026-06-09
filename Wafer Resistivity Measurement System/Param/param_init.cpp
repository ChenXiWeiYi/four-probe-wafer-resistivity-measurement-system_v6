#include "widget.h"
#include "ui_widget.h"
#include <QMap>
#include <QDebug>

namespace {
/**
 * @brief ParseDoubleVector
 * @author 刘嘉诚
 * @date 2026.06.08
 */
bool ParseDoubleVector(const QString &str, int expectedSize, QVector<double> *values)
{
    QStringList parts = str.split(",");
    if(parts.size() != expectedSize){
        return false;
    }

    QVector<double> parsed;
    parsed.reserve(expectedSize);
    for(const QString &part : parts){
        bool ok = false;
        double value = part.trimmed().toDouble(&ok);
        if(!ok){
            return false;
        }
        parsed.append(value);
    }

    *values = parsed;
    return true;
}
}

/**
 * @brief Init_Param_Channel
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Init_Param_Channel(void)
{
    bool ok1, ok2;
    int currPos = Param_Setting_Read(NAME_CurrPos).toInt(&ok1);
    int volRange = Param_Setting_Read(NAME_VolRange).toInt(&ok2);
    if(!ok1 || !ok2){
        Popup_Window("错误", "档位初始化失败!\n请修改为正确数值后重启。");
        return;
    }
    if(currPos < 0 || currPos > 7){
        Popup_Window("错误", "电流档位不在范围内");
        return;
    }
    if(volRange < 0 || volRange > 3){
        Popup_Window("错误", "电压档位不在范围内");
        return;
    }

    Param_used.CurrPos = currPos;
    Param_used.VolRange = volRange;
    ui->Button_CurrPos->setText(Map_CurrPos.value(static_cast<CurrPos_TypeDef>(Param_used.CurrPos)));
    ui->Button_VolRange->setText(Map_VolRange.value(static_cast<VolRange_TypeDef>(Param_used.VolRange)));
}

/**
 * @brief Init_Param_ab
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Init_Param_ab(void)
{
    bool ok1, ok2;
    double a = Param_Setting_Read(NAME_a).toDouble(&ok1);
    double b = Param_Setting_Read(NAME_b).toDouble(&ok2);
    if(!ok1 || !ok2){
        Popup_Window("错误", "ab初始化失败!\n请修改为正确数值后重启。");
        ui->cin_a->clear();
        ui->cin_b->clear();
        return;
    }

    Param_used.a = a;
    Param_used.b = b;
    ui->cin_a->setText(QString::number(Param_used.a));
    ui->cin_b->setText(QString::number(Param_used.b));
}

/**
 * @brief Init_Param_Temperature
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Init_Param_Temperature(void)
{
    bool ok;
    double val = Param_Setting_Read(NAME_Temperature).toDouble(&ok);
    if(!ok){
        Popup_Window("错误", "样品温度初始化失败!\n请修改为正确数值后重启。");
        ui->cin_Temperature->clear();
        return;
    }

    Param_used.Temperature = val;
    ui->cin_Temperature->setText(QString::number(Param_used.Temperature));
}

/**
 * @brief Init_Param_CurrErrorBound
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Init_Param_CurrErrorBound(void)
{
    bool ok;
    double val = Param_Setting_Read(NAME_CurrErrorBound).toDouble(&ok);
    if(!ok){
        Popup_Window("错误", "电流误差范围初始化失败!\n请修改为正确数值后重启。");
        ui->cin_CurrErrorBound->clear();
        return;
    }

    Param_used.CurrErrorBound = val;
    ui->cin_CurrErrorBound->setText(QString::number(Param_used.CurrErrorBound));
}

/**
 * @brief Init_Param_Thickness
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Init_Param_Thickness(void)
{
    bool ok;
    double val = Param_Setting_Read(NAME_SampleThickness).toDouble(&ok);
    if(!ok){
        Popup_Window("错误", "样品厚度初始化失败!\n请修改为正确数值后重启。");
        ui->cin_Thickness->clear();
        return;
    }

    Param_used.SampleThickness = val;
    ui->cin_Thickness->setText(QString::number(Param_used.SampleThickness));
}

/**
 * @brief Init_Param_ProbeSpacing
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Init_Param_ProbeSpacing(void)
{
    bool ok;
    double val = Param_Setting_Read(NAME_ProbeSpacing).toDouble(&ok);
    if(!ok){
        Popup_Window("错误", "探针间距初始化失败!\n请修改为正确数值后重启。");
        ui->cin_ProbeSpacing->clear();
        return;
    }

    Param_used.ProbeSpacing = val;
    ui->cin_ProbeSpacing->setText(QString::number(Param_used.ProbeSpacing));
}

/**
 * @brief Init_Param_SampleDiameter
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Init_Param_SampleDiameter(void)
{
    bool ok;
    double val = Param_Setting_Read(NAME_SampleDiameter).toDouble(&ok);
    if(!ok){
        Popup_Window("错误", "样品直径初始化失败!\n请修改为正确数值后重启。");
        ui->cin_SampleDiameter->clear();
        return;
    }

    Param_used.SampleDiameter = val;
    ui->cin_SampleDiameter->setText(QString::number(Param_used.SampleDiameter));
}

/**
 * @brief Init_Param_FspCorrectionFactor
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Init_Param_FspCorrectionFactor(void)
{
    bool ok;
    double val = Param_Setting_Read(NAME_FspCorrectionFactor).toDouble(&ok);
    if(!ok){
        Popup_Window("错误", "探针修正系数初始化失败!\n请修改为正确数值后重启。");
        ui->cin_FspCorrectionFactor->clear();
        return;
    }

    Param_used.FspCorrectionFactor = val;
    ui->cin_FspCorrectionFactor->setText(QString::number(Param_used.FspCorrectionFactor));
}

/**
 * @brief Init_Param_SemiType
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Init_Param_SemiType(void)
{
    bool ok;
    int val = Param_Setting_Read(NAME_SemiType).toInt(&ok);
    if(!ok || (val != 0 && val != 1)){
        Popup_Window("错误", "半导体类型初始化失败!\n请修改为正确数值后重启。");
        return;
    }

    Param_used.SemiType = static_cast<SemiType_TypeDef>(val);
    ui->Button_SelSemiType->setText(Param_used.SemiType == SEMITYPE_P ? "P" : "N");
}

/**
 * @brief Init_Param_ControlVoltages
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Init_Param_ControlVoltages(void)
{
    QString str = Param_Setting_Read(NAME_ControlVoltages).toString();
    QStringList parts = str.split(",");
    bool ok;
    for(int i = 0; i < parts.size() && i < Param_used.ControlVoltages.size(); i++){
        Param_used.ControlVoltages[i] = parts[i].trimmed().toFloat(&ok);
        if(!ok){
            Popup_Window("错误", "恒流源压控电压初始化失败!\n请修改为正确数值后重启。");
            return;
        }
    }
}

/**
 * @brief Init_Param_PIDParameters
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Init_Param_PIDParameters(void)
{
    QVector<double> kp;
    QVector<double> ti;
    QVector<double> td;

    if(!ParseDoubleVector(Param_Setting_Read(NAME_PID_Kp).toString(), 7, &kp) ||
       !ParseDoubleVector(Param_Setting_Read(NAME_PID_Ti).toString(), 7, &ti) ||
       !ParseDoubleVector(Param_Setting_Read(NAME_PID_Td).toString(), 7, &td)){
        Popup_Window("错误", "PID参数初始化失败!\n请检查Param.Setting中的PID_Kp/PID_Ti/PID_Td。");
        return;
    }

    Param_used.PID_Kp = kp;
    Param_used.PID_Ti = ti;
    Param_used.PID_Td = td;
    Load_PIDParamsForCurrentPosition();
}

/**
 * @brief Init_Param_PIDControlEnabled
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Init_Param_PIDControlEnabled(void)
{
    bool ok;
    int val = Param_Setting_Read(NAME_PIDControlEnabled).toInt(&ok);
    if(!ok || (val != 0 && val != 1)){
        Popup_Window("错误", "PID启用后门初始化失败!\n请将PIDControlEnabled设置为0或1。");
        Param_used.PIDControlEnabled = false;
    }else{
        Param_used.PIDControlEnabled = (val == 1);
    }

    ui->ToolButton_ControlAlgo->setText(Param_used.PIDControlEnabled ? "PID控制:开启" : "PID控制:关闭");
    ui->ToolButton_ControlAlgo->setEnabled(false);
}
