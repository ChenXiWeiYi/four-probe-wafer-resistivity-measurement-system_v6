#include "widget.h"
#include "ui_widget.h"

void Widget::Add_Resistivity2Table(double value)
{
    if(MeasureState_used.MeasureDirection == MEASUREDIRECTION_FORWARD){
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, value);
        ui->TableWidget_f->setItem(MeasureState_used.cnt_MeasureTimes + 1, MeasureState_used.cnt_MeasureGroup, item);    // 第一行存信息
    }else{
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, value);
        ui->TableWidget_r->setItem(MeasureState_used.cnt_MeasureTimes + 1, MeasureState_used.cnt_MeasureGroup, item);
    }
    MeasureState_used.cnt_MeasureTimes ++;
}
