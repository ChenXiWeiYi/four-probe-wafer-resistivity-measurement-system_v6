#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

/**
 * @brief Widget::onButtonabClicked ab参数修改槽函数
 * @author 刘嘉诚
 * @date 2026.02.18
 */
void Widget::onButtonabClicked()
{
    bool ok1, ok2;
    double a = ui->cin_a->text().toDouble(&ok1);
    double b = ui->cin_b->text().toDouble(&ok2);

    if (!ok1 || !ok2) {
        Popup_Window("错误", "输入a或b格式错误!");
        ui->cin_a->setText(QString::number(Param_used.a));
        ui->cin_b->setText(QString::number(Param_used.b));
        return;
    }
    if (qAbs(a - Param_used.a) < 0.000001 && qAbs(b - Param_used.b) < 0.000001) return;
    if(MeasureState_used.MeasureStage != STAGE_IDLE){
        Popup_Window("错误", "正在测量, 禁止修改参数!");
        ui->cin_a->setText(QString::number(Param_used.a));
        ui->cin_b->setText(QString::number(Param_used.b));
        return;
    }
    if (true || Popup_Confirm_Dialog("提示", "是否保存并使用该ab?")) {
        Param_used.a = a;
        Param_used.b = b;
        Param_Setting_Write(NAME_a, a);
        Param_Setting_Write(NAME_b, b);
    }
    ui->cin_a->setText(QString::number(Param_used.a));
    ui->cin_b->setText(QString::number(Param_used.b));
}

/**
 * @brief Widget::onButtonCurrErrorBoundClicked 电流误差范围修改槽函数
 * @author 刘嘉诚
 * @date 2026.02.18
 */
void Widget::onButtonCurrErrorBoundClicked()
{
    bool ok;
    double val = ui->cin_CurrErrorBound->text().toDouble(&ok);

    if (!ok) {
        Popup_Window("错误", "输入电流误差范围格式错误!");
        ui->cin_CurrErrorBound->setText(QString::number(Param_used.CurrErrorBound));
        return;
    }

    if (qAbs(val - Param_used.CurrErrorBound) < 0.000001) return;

    if(MeasureState_used.MeasureStage != STAGE_IDLE){
        Popup_Window("错误", "正在测量, 禁止修改参数!");
        ui->cin_CurrErrorBound->setText(QString::number(Param_used.CurrErrorBound));
        return;
    }

    if (true || Popup_Confirm_Dialog("提示", "是否保存并使用该误差范围?")) {
        Param_used.CurrErrorBound = val;
        Param_Setting_Write(NAME_CurrErrorBound, val);
        Command_SendPIDControlConfig();
    }

    ui->cin_CurrErrorBound->setText(QString::number(Param_used.CurrErrorBound));
}

/**
 * @brief Widget::onButtonTemperatureClicked 温度参数修改槽函数
 * @author 刘嘉诚
 * @date 2026.02.18
 */
void Widget::onButtonTemperatureClicked()
{
    bool ok;
    double val = ui->cin_Temperature->text().toDouble(&ok);

    if (!ok) {
        Popup_Window("错误", "输入温度格式错误!");
        ui->cin_Temperature->setText(QString::number(Param_used.Temperature));
        return;
    }

    if (qAbs(val - Param_used.Temperature) < 0.000001) return;

    if(MeasureState_used.MeasureStage != STAGE_IDLE){
        Popup_Window("错误", "正在测量, 禁止修改参数!");
        ui->cin_Temperature->setText(QString::number(Param_used.Temperature));
        return;
    }

    if (true || Popup_Confirm_Dialog("提示", "是否保存并使用该温度?")) {
        Param_used.Temperature = val;
        Param_Setting_Write(NAME_Temperature, val);
    }

    ui->cin_Temperature->setText(QString::number(Param_used.Temperature));
}

/**
 * @brief Widget::onButtonThicknessClicked 样品厚度修改槽函数
 * @author 刘嘉诚
 * @date 2026.02.18
 */
void Widget::onButtonThicknessClicked()
{
    bool ok;
    double val = ui->cin_Thickness->text().toDouble(&ok);

    if (!ok) {
        Popup_Window("错误", "输入样品厚度格式错误!");
        ui->cin_Thickness->setText(QString::number(Param_used.SampleThickness));
        return;
    }

    if (qAbs(val - Param_used.SampleThickness) < 0.000001) return;

    if(MeasureState_used.MeasureStage != STAGE_IDLE){
        Popup_Window("错误", "正在测量, 禁止修改参数!");
        ui->cin_Thickness->setText(QString::number(Param_used.SampleThickness));
        return;
    }

    if (true || Popup_Confirm_Dialog("提示", "是否保存并使用该样品厚度?")) {
        Param_used.SampleThickness = val;
        Param_Setting_Write(NAME_SampleThickness, val);
    }

    ui->cin_Thickness->setText(QString::number(Param_used.SampleThickness));
}

/**
 * @brief Widget::onButtonProbeSpacingClicked 探针间距修改槽函数
 * @author 刘嘉诚
 * @date 2026.02.18
 */
void Widget::onButtonProbeSpacingClicked()
{
    bool ok;
    double val = ui->cin_ProbeSpacing->text().toDouble(&ok);

    if (!ok) {
        Popup_Window("错误", "输入探针间距格式错误!");
        ui->cin_ProbeSpacing->setText(QString::number(Param_used.ProbeSpacing));
        return;
    }

    if (qAbs(val - Param_used.ProbeSpacing) < 0.000001) return;

    if(MeasureState_used.MeasureStage != STAGE_IDLE){
        Popup_Window("错误", "正在测量, 禁止修改参数!");
        ui->cin_ProbeSpacing->setText(QString::number(Param_used.ProbeSpacing));
        return;
    }

    if (true || Popup_Confirm_Dialog("提示", "是否保存并使用该探针间距?")) {
        Param_used.ProbeSpacing = val;
        Param_Setting_Write(NAME_ProbeSpacing, val);
    }

    ui->cin_ProbeSpacing->setText(QString::number(Param_used.ProbeSpacing));
}

/**
 * @brief Widget::onButtonSampleDiameterClicked 样品直径修改槽函数
 * @author 刘嘉诚
 * @date 2026.02.18
 */
void Widget::onButtonSampleDiameterClicked()
{
    bool ok;
    double val = ui->cin_SampleDiameter->text().toDouble(&ok);

    if (!ok) {
        Popup_Window("错误", "输入样品直径格式错误!");
        ui->cin_SampleDiameter->setText(QString::number(Param_used.SampleDiameter));
        return;
    }

    if (qAbs(val - Param_used.SampleDiameter) < 0.000001) return;

    if(MeasureState_used.MeasureStage != STAGE_IDLE){
        Popup_Window("错误", "正在测量, 禁止修改参数!");
        ui->cin_SampleDiameter->setText(QString::number(Param_used.SampleDiameter));
        return;
    }

    if (true || Popup_Confirm_Dialog("提示", "是否保存并使用该样品直径?")) {
        Param_used.SampleDiameter = val;
        Param_Setting_Write(NAME_SampleDiameter, val);
    }

    ui->cin_SampleDiameter->setText(QString::number(Param_used.SampleDiameter));
}

/**
 * @brief Widget::onButtonFspCorrectionFactorClicked 探针修正系数修改槽函数
 * @author 刘嘉诚
 * @date 2026.02.18
 */
void Widget::onButtonFspCorrectionFactorClicked()
{
    bool ok;
    double val = ui->cin_FspCorrectionFactor->text().toDouble(&ok);

    if (!ok) {
        Popup_Window("错误", "探针修正系数格式错误!");
        ui->cin_FspCorrectionFactor->setText(QString::number(Param_used.FspCorrectionFactor));
        return;
    }

    if (qAbs(val - Param_used.FspCorrectionFactor) < 0.000001) return;

    if(MeasureState_used.MeasureStage != STAGE_IDLE){
        Popup_Window("错误", "正在测量, 禁止修改参数!");
        ui->cin_FspCorrectionFactor->setText(QString::number(Param_used.FspCorrectionFactor));
        return;
    }

    if (true || Popup_Confirm_Dialog("提示", "是否保存并使用该探针修正系数?")) {
        Param_used.FspCorrectionFactor = val;
        Param_Setting_Write(NAME_FspCorrectionFactor, val);
    }

    ui->cin_FspCorrectionFactor->setText(QString::number(Param_used.FspCorrectionFactor));
}

/**
 * @brief Widget::onButtonControlVoltageClicked 恒流源压控电压修改槽函数
 * @author 刘嘉诚
 * @date 2026.02.18
 */
void Widget::onButtonControlVoltageClicked()
{
    bool ok;
    float val = ui->cin_ControlVoltage->text().toFloat(&ok);

    if (!ok) {
        Popup_Window("错误", "该档位压控电压格式错误!");
        ui->cin_ControlVoltage->setText(QString::number(Param_used.ControlVoltages[static_cast<int>(Param_used.CurrPos)]));
        return;
    }

    if(MeasureState_used.MeasureStage != STAGE_IDLE){
        Popup_Window("错误", "正在测量, 禁止修改参数!");
        ui->cin_ControlVoltage->setText(QString::number(Param_used.ControlVoltages[static_cast<int>(Param_used.CurrPos)]));
        return;
    }

    if(Popup_Confirm_Dialog("提示", "是否对该档位保存并使用该压控电压?")){
        Param_used.ControlVoltages[static_cast<int>(Param_used.CurrPos)] = val;
        Command_ModifyControlVoltage();
    }

    ui->cin_ControlVoltage->setText(QString::number(Param_used.ControlVoltages[static_cast<int>(Param_used.CurrPos)]));
}

/**
 * @brief Widget::onButtonSelSemiTypeClicked 切换P/N类型槽函数
 * @author 刘嘉诚
 * @date 2026.02.18
 */
void Widget::onButtonSelSemiTypeClicked()
{
    if(MeasureState_used.MeasureStage != STAGE_IDLE){
        Popup_Window("错误", "正在测量, 禁止修改参数!");
        return;
    }

    // 没得输入框,不用校验格式,直接切
    if (Param_used.SemiType == SEMITYPE_P) {
        Param_used.SemiType = SEMITYPE_N;
    } else {
        Param_used.SemiType = SEMITYPE_P;
    }

    ui->Button_SelSemiType->setText(Param_used.SemiType == SEMITYPE_P ? "P" : "N");
    Param_Setting_Write(NAME_SemiType, static_cast<int>(Param_used.SemiType));
}

/**
 * @brief Widget::onButtonSemiTypeClicked (已弃用) 半导体类型保存确认
 * @author 刘嘉诚
 * @date 2026.02.18
 */
void Widget::onButtonSemiTypeClicked()
{
    if(MeasureState_used.MeasureStage != STAGE_IDLE){
        Popup_Window("错误", "正在测量,禁止修改参数!");
        return;
    }
    if(true || Popup_Confirm_Dialog("提示", "是否保存该半导体类型?")){
        Param_Setting_Write(NAME_SemiType, static_cast<int>(Param_used.SemiType));
    }
}
