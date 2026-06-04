#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QAction>

/**
 * @brief Widget::onMenuCurrPosTriggered 选电流档位槽函数
 * 船新版本,好看多了
 * @param action 点击的档位
 * @author 刘嘉诚
 * @date 2026.02.15
 */
void Widget::onMenuCurrPosTriggered(QAction *action)
{
    int CurrPos_i = action->data().toInt();

    if(MeasureState_used.MeasureStage != STAGE_IDLE){
        Popup_Window("错误","正在测量,禁止修改参数!");
        return;
    }
    Param_used.CurrPos = CurrPos_i;
    ui->Button_CurrPos->setText("正在切换");
    ui->cin_ControlVoltage->setText("正在切换电流档位");
    Controller_used.Last_uk = Param_used.ControlVoltages[static_cast<int>(Param_used.CurrPos)];
    Command_SwitchCurrPos();
}


/**
 * @brief Widget::onMenuVolRangeTriggered 选电压档位槽函数
 * 船新版本,好看多了
 * @param action 点击的档位
 * @author 刘嘉诚
 * @date 2026.02.15
 */
void Widget::onMenuVolRangeTriggered(QAction *action)
{
    int VolRange_i = action->data().toInt();

    if(MeasureState_used.MeasureStage != STAGE_IDLE){
        Popup_Window("错误","正在测量,禁止修改参数!");
        return;
    }
    ui->Button_VolRange->setText("正在切换");
    Param_used.VolRange = VolRange_i;
    Command_SwitchVolRange();
}

/**
 * @brief Widget::onMenuMeasureModeTriggered 选测量模式
 * @param action 点击的档位
 * @author 刘嘉诚
 * @date 2026.02.15
 */
void Widget::onMenuMeasureModeTriggered(QAction *action)
{
    int MeasureMode_i = action->data().toInt();

    if(MeasureState_used.MeasureStage != STAGE_IDLE){
        Popup_Window("错误","正在测量,禁止修改参数!");
        return;
    }

    Param_used.MeasureMode = static_cast<MeasureMode_TypeDef>(MeasureMode_i);
    Param_Setting_Write(NAME_MeasureMode, MeasureMode_i);   // 存入文件

    ui->ToolButton_MeasureMode->setText(action->text());
}

/**
 * @brief Widget::onMenuCOMTriggered 选择COM口
 */
void Widget::onMenuCOMTriggered(QAction *action)
{
    QString comName = action->text();

    serialPort->close();
    serialPort->setPortName(comName);

    if(!serialPort->open(QIODevice::ReadWrite)){
        qDebug() << comName << "打开失败";
        ui->logText_1->append(QString("错误: 无法打开 %1 - %2").arg(comName).arg(serialPort->errorString()));
        ui->Button_SelCOM->setText("---");
        action->setChecked(false);
    }else{
        qDebug() << comName << "打开成功";
        ui->logText_1->append(QString("成功: 打开 %1").arg(comName));
        ui->Button_SelCOM->setText(comName);
    }
}

void Widget::onMenuControlAlgoTriggered(QAction *action)
{
    int ControlAlgo_i = action->data().toInt();

    if(MeasureState_used.MeasureStage != STAGE_IDLE){
        Popup_Window("错误","正在测量,禁止修改参数!");
        return;
    }

    Param_used.ControlAlgo = static_cast<ControlAlgo_TypeDef>(ControlAlgo_i);
    Param_Setting_Write(NAME_ControlAlgorithm, ControlAlgo_i);   // 存入文件

    ui->ToolButton_ControlAlgo->setText(action->text());
}
