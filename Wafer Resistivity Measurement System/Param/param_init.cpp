#include "widget.h"
#include "ui_widget.h"
#include <QMap>
#include <QDebug>

/**
 * @brief Widget::Init_Param_Channel 初始化测量档位
 * @author 刘嘉诚
 * @date 2026.02.17
 */
void Widget::Init_Param_Channel(void)
{
    bool ok1, ok2;
    int currPos = Param_Setting_Read(NAME_CurrPos).toInt(&ok1);
    int volRange = Param_Setting_Read(NAME_VolRange).toInt(&ok2);
    if (!ok1 || !ok2) {
        Popup_Window("错误", "档位初始化失败!\n请修改为正确数值后重启。");
        return;
    }
    if (currPos < 0 || currPos > 7) {
        Popup_Window("错误", "电流档位不在范围内!");
        return;
    }
    if (volRange < 0 || volRange > 3) {
        Popup_Window("错误", "电压档位不在范围内!");
        return;
    }
    Param_used.CurrPos = currPos;
    Param_used.VolRange = volRange;
    ui->Button_CurrPos->setText(Map_CurrPos.value(static_cast<CurrPos_TypeDef>(Param_used.CurrPos)));
    ui->Button_VolRange->setText(Map_VolRange.value(static_cast<VolRange_TypeDef>(Param_used.VolRange)));
}

/**
 * @brief Widget::Init_Param_ab 初始化ab值
 * @author 刘嘉诚
 * @date 2026.02.17
 */
void Widget::Init_Param_ab(void)
{
    bool ok1, ok2;
    double a = Param_Setting_Read(NAME_a).toDouble(&ok1);
    double b = Param_Setting_Read(NAME_b).toDouble(&ok2);
    if (!ok1 || !ok2) {
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
 * @brief Widget::Init_Param_Temperature 初始化温度
 * @author 刘嘉诚
 * @date 2026.02.17
 */
void Widget::Init_Param_Temperature(void)
{
    bool ok;
    double val = Param_Setting_Read(NAME_Temperature).toDouble(&ok);
    if (!ok) {
        Popup_Window("错误", "样品温度初始化失败!\n请修改为正确数值后重启。");
        ui->cin_Temperature->clear();
        return;
    }
    Param_used.Temperature = val;
    ui->cin_Temperature->setText(QString::number(Param_used.Temperature));
}

/**
 * @brief Widget::Init_Param_CurrErrorBound 初始化电流误差范围
 * @author 刘嘉诚
 * @date 2026.02.17
 */
void Widget::Init_Param_CurrErrorBound(void)
{
    bool ok;
    double val = Param_Setting_Read(NAME_CurrErrorBound).toDouble(&ok);
    if (!ok) {
        Popup_Window("错误", "电流误差范围初始化失败!\n请修改为正确数值后重启。");
        ui->cin_CurrErrorBound->clear();
        return;
    }
    Param_used.CurrErrorBound = val;
    ui->cin_CurrErrorBound->setText(QString::number(Param_used.CurrErrorBound));
}


/**
 * @brief Widget::Init_Param_Thickness 初始化样品厚度
 * @author 刘嘉诚
 * @date 2026.02.17
 */
void Widget::Init_Param_Thickness(void)
{
    bool ok;
    double val = Param_Setting_Read(NAME_SampleThickness).toDouble(&ok);
    if (!ok) {
        Popup_Window("错误", "样品厚度初始化失败!\n请修改为正确数值后重启。");
        ui->cin_Thickness->clear();
        return;
    }
    Param_used.SampleThickness = val;
    ui->cin_Thickness->setText(QString::number(Param_used.SampleThickness));
}

/**
 * @brief Widget::Init_Param_ProbeSpacing 初始化探针间距
 * @author 刘嘉诚
 * @date 2026.02.17
 */
void Widget::Init_Param_ProbeSpacing(void)
{
    bool ok;
    double val = Param_Setting_Read(NAME_ProbeSpacing).toDouble(&ok);
    if (!ok) {
        Popup_Window("错误", "探针间距初始化失败!\n请修改为正确数值后重启。");
        ui->cin_ProbeSpacing->clear();
        return;
    }
    Param_used.ProbeSpacing = val;
    ui->cin_ProbeSpacing->setText(QString::number(Param_used.ProbeSpacing));
}

/**
 * @brief Widget::Init_Param_SampleDiameter 初始化样品直径
 * @author 刘嘉诚
 *  @date 2026.02.17
 */
void Widget::Init_Param_SampleDiameter(void)
{
    bool ok;
    double val = Param_Setting_Read(NAME_SampleDiameter).toDouble(&ok);
    if (!ok) {
        Popup_Window("错误", "样品直径初始化失败!\n请修改为正确数值后重启。");
        ui->cin_SampleDiameter->clear();
        return;
    }
    Param_used.SampleDiameter = val;
    ui->cin_SampleDiameter->setText(QString::number(Param_used.SampleDiameter));
}

/**
 * @brief Widget::Init_Param_FspCorrectionFactor 初始化探针修正系数
 * @author 刘嘉诚
 * @date 2026.02.17
 */
void Widget::Init_Param_FspCorrectionFactor(void)
{
    bool ok;
    double val = Param_Setting_Read(NAME_FspCorrectionFactor).toDouble(&ok);
    if (!ok) {
        Popup_Window("错误", "探针修正系数初始化失败!\n请修改为正确数值后重启。");
        ui->cin_FspCorrectionFactor->clear();
        return;
    }
    Param_used.FspCorrectionFactor = val;
    ui->cin_FspCorrectionFactor->setText(QString::number(Param_used.FspCorrectionFactor));
}

/**
 * @brief Widget::Init_Param_SemiType 初始化半导体类型
 * @author 刘嘉诚
 * @date 2026.02.17
 */
void Widget::Init_Param_SemiType(void)
{
    bool ok;
    int val = Param_Setting_Read(NAME_SemiType).toInt(&ok);
    if (!ok || (val != 0 && val != 1)) {
        Popup_Window("错误", "半导体类型初始化失败!\n请修改为正确数值后重启。");
        return;
    }
    Param_used.SemiType = static_cast<SemiType_TypeDef>(val);
    ui->Button_SelSemiType->setText(Param_used.SemiType == SEMITYPE_P ? "P" : "N");
}

/**
 * @brief Widget::Init_Param_ControlVoltages 初始化恒流源压控电压
 * @author 刘嘉诚
 * @date 2026.02.17
 */
void Widget::Init_Param_ControlVoltages(void)
{
    QString str = Param_Setting_Read(NAME_ControlVoltages).toString();
    QStringList parts = str.split(",");
    bool ok;
    for(int i = 0; i < parts.size() && i < Param_used.ControlVoltages.size(); i++) {
        QString temp;
        temp = parts[i].trimmed();
        Param_used.ControlVoltages[i] = temp.toFloat(&ok);
        if(!ok){
            Popup_Window("错误", "恒流源压控电压初始化失败!\n请修改为正确数值后重启。");
            return;
        }
    }
}

/**
 * @brief Widget::Init_Param_ControlAlgo 初始化电流控制算法
 * @author 刘嘉诚
 * @date 2026.03.10
 */
void Widget::Init_Param_ControlAlgo(void)
{
    bool ok;
    int val = Param_Setting_Read(NAME_ControlAlgorithm).toInt(&ok);
    if (!ok || (val < 0 || val > 3)) {
        Popup_Window("错误", "电流控制算法初始化失败!\n请修改为正确数值后重启。");
        return;
    }
    Param_used.ControlAlgo = static_cast<ControlAlgo_TypeDef>(val);
    ui->ToolButton_ControlAlgo->setText(Map_ControlAlgo.value(static_cast<ControlAlgo_TypeDef>(Param_used.ControlAlgo)));
}
