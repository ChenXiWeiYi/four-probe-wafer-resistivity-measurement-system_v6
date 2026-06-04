#include "widget.h"
#include "ui_widget.h"
#include <QAction>
#include <QActionGroup>
#include <QMenu>
#include <QToolButton>

/**
 * @brief Widget::Init_Menu 初始化全部菜单
 * @author 刘嘉诚
 * @date 2026.06.04
 */
void Widget::Init_Menu(void)
{
    Init_Menu_CurrPos();
    Init_Menu_VolRange();
    Init_Menu_MeasureMode();
    Init_Menu_ControlAlgo();
    Init_Menu_COM();
}

/**
 * @brief Widget::Init_Menu_CurrPos 初始化电流档位菜单
 * @author 刘嘉诚
 * @date 2026.06.04
 */
void Widget::Init_Menu_CurrPos(void)
{
    Menu_CurrPos = new QMenu(this);
    QActionGroup *Menu_CurrPosGroup = new QActionGroup(this);

    for(auto it = Map_CurrPos.constBegin(); it != Map_CurrPos.constEnd(); it++){
        CurrPos_TypeDef enumID = it.key();
        QString menuText = it.value();
        QAction *action = new QAction(menuText, this);
        action->setData(static_cast<int>(enumID));
        action->setCheckable(true);
        Menu_CurrPosGroup->addAction(action);
        Menu_CurrPos->addAction(action);
    }

    connect(Menu_CurrPosGroup, &QActionGroup::triggered, this, &Widget::onMenuCurrPosTriggered);
    ui->Button_CurrPos->setPopupMode(QToolButton::InstantPopup);
    ui->Button_CurrPos->setMenu(Menu_CurrPos);
}

/**
 * @brief Widget::Init_Menu_VolRange 初始化电压档位菜单
 * @author 刘嘉诚
 * @date 2026.06.04
 */
void Widget::Init_Menu_VolRange(void)
{
    Menu_VolRange = new QMenu(this);
    QActionGroup *Menu_VolRangeGroup = new QActionGroup(this);

    for(auto it = Map_VolRange.constBegin(); it != Map_VolRange.constEnd(); it++){
        VolRange_TypeDef enumID = it.key();
        QString menuText = it.value();
        QAction *action = new QAction(menuText, this);
        action->setData(static_cast<int>(enumID));
        action->setCheckable(true);
        Menu_VolRangeGroup->addAction(action);
        Menu_VolRange->addAction(action);
    }

    connect(Menu_VolRangeGroup, &QActionGroup::triggered, this, &Widget::onMenuVolRangeTriggered);
    ui->Button_VolRange->setPopupMode(QToolButton::InstantPopup);
    ui->Button_VolRange->setMenu(Menu_VolRange);
}

/**
 * @brief Widget::Init_Menu_MeasureMode 初始化测量模式菜单
 * @author 刘嘉诚
 * @date 2026.06.04
 */
void Widget::Init_Menu_MeasureMode(void)
{
    Menu_MeasureMode = new QMenu(this);
    QActionGroup *Menu_MeasureModeGroup = new QActionGroup(this);

    for(auto it = Map_MeasureMode.constBegin(); it != Map_MeasureMode.constEnd(); it++){
        MeasureMode_TypeDef enumID = it.key();
        QString menuText = it.value();
        QAction *action = new QAction(menuText, this);
        action->setData(static_cast<int>(enumID));
        action->setCheckable(true);
        Menu_MeasureModeGroup->addAction(action);
        Menu_MeasureMode->addAction(action);
    }

    connect(Menu_MeasureModeGroup, &QActionGroup::triggered, this, &Widget::onMenuMeasureModeTriggered);
    ui->ToolButton_MeasureMode->setPopupMode(QToolButton::InstantPopup);
    ui->ToolButton_MeasureMode->setMenu(Menu_MeasureMode);
}

/**
 * @brief Widget::Init_Menu_ControlAlgo 初始化电流闭环算法菜单
 * @author 刘嘉诚
 * @date 2026.06.04
 */
void Widget::Init_Menu_ControlAlgo(void)
{
    Menu_ControlAlgo = new QMenu(this);
    QActionGroup *Menu_ControlAlgoGroup = new QActionGroup(this);

    for(auto it = Map_ControlAlgo.constBegin(); it != Map_ControlAlgo.constEnd(); it++){
        ControlAlgo_TypeDef enumID = it.key();
        QString menuText = it.value();
        QAction *action = new QAction(menuText, this);
        action->setData(static_cast<int>(enumID));
        action->setCheckable(true);
        Menu_ControlAlgoGroup->addAction(action);
        Menu_ControlAlgo->addAction(action);
    }

    connect(Menu_ControlAlgoGroup, &QActionGroup::triggered, this, &Widget::onMenuControlAlgoTriggered);
    ui->ToolButton_ControlAlgo->setPopupMode(QToolButton::InstantPopup);
    ui->ToolButton_ControlAlgo->setMenu(Menu_ControlAlgo);
}

/**
 * @brief Widget::Init_Menu_COM 初始化COM口选择菜单
 * @author 刘嘉诚
 * @date 2026.06.04
 */
void Widget::Init_Menu_COM(void)
{
    Menu_COM = new QMenu(this);
    QActionGroup *Menu_COMGroup = new QActionGroup(this);

    for(int i = 1; i <= 10; ++i){
        QString comName = QString("COM%1").arg(i);
        QAction *action = new QAction(comName, this);
        action->setCheckable(true);
        Menu_COMGroup->addAction(action);
        Menu_COM->addAction(action);
    }

    connect(Menu_COMGroup, &QActionGroup::triggered, this, &Widget::onMenuCOMTriggered);
    ui->Button_SelCOM->setPopupMode(QToolButton::InstantPopup);
    ui->Button_SelCOM->setMenu(Menu_COM);
}
