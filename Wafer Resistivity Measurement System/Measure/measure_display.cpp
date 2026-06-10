#include "widget.h"
#include "ui_widget.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QtMath>

static const int RoleForwardResistivity = Qt::UserRole + 1;
static const int RoleMeanResistivity = Qt::UserRole + 2;

static QString UnitOhm(void)
{
    return QString(QChar(0x03A9));
}

static QString UnitOhmCm(void)
{
    return QString(QChar(0x03A9)) + QString(QChar(0x00B7)) + QStringLiteral("cm");
}

static QString FormatMeasureNumber(double value)
{
    if(!qIsFinite(value)){
        return QStringLiteral("--");
    }
    return QString::number(value, 'g', 8);
}

static QString FormatMeasureValue(double value, const QString &unit)
{
    if(!qIsFinite(value)){
        return QStringLiteral("-- ") + unit;
    }
    return FormatMeasureNumber(value) + QStringLiteral(" ") + unit;
}

static bool ReadFiniteItemData(QTableWidgetItem *item, int role, double *value)
{
    if(!item){
        return false;
    }

    bool ok = false;
    const double data = item->data(role).toDouble(&ok);
    if(!ok || !qIsFinite(data)){
        return false;
    }

    *value = data;
    return true;
}

static QTableWidgetItem *EnsureTableItem(QTableWidget *table, int row, int column)
{
    QTableWidgetItem *item = table->item(row, column);
    if(!item){
        item = new QTableWidgetItem();
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        table->setItem(row, column, item);
    }
    return item;
}

static void SetDebugTableItem(QTableWidget *table, int row, int column, const QString &text)
{
    QTableWidgetItem *item = new QTableWidgetItem(text);
    item->setTextAlignment(Qt::AlignCenter);
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    table->setItem(row, column, item);
}

static void AppendDebugMeasureRow(QTableWidget *table,
                                  int groupIndex,
                                  int measureIndex,
                                  const MeasureValueStruct_TypeDef &value)
{
    if(!table){
        return;
    }

    const int row = table->rowCount();
    table->insertRow(row);
    SetDebugTableItem(table, row, 0, QString::number(groupIndex + 1));
    SetDebugTableItem(table, row, 1, QString::number(measureIndex + 1));
    SetDebugTableItem(table, row, 2, FormatMeasureNumber(value.Voltage));
    SetDebugTableItem(table, row, 3, FormatMeasureNumber(value.Current));
}

/**
 * @brief Update_RealtimeMeasureDisplay
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void Widget::Update_RealtimeMeasureDisplay(double Voltage, double Current, double Resistance, double Resistivity)
{
    ui->Label_VoltData->setText(FormatMeasureValue(Voltage, QStringLiteral("V")));
    ui->Label_CurrData->setText(FormatMeasureValue(Current, QStringLiteral("A")));
    ui->lblRealtimeResistance->setText(FormatMeasureValue(Resistance, UnitOhm()));
    ui->Label_ResData->setText(FormatMeasureValue(Resistivity, UnitOhmCm()));
}

/**
 * @brief Update_ResultStatistics
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void Widget::Update_ResultStatistics(void)
{
    QVector<double> values;
    values.reserve(ui->TableWidget_f->rowCount() * ui->TableWidget_f->columnCount());

    for(int row = 0; row < ui->TableWidget_f->rowCount(); ++row){
        for(int column = 0; column < ui->TableWidget_f->columnCount(); ++column){
            double value = 0.0;
            if(ReadFiniteItemData(ui->TableWidget_f->item(row, column), RoleMeanResistivity, &value)){
                values.append(value);
            }
        }
    }

    if(values.isEmpty()){
        ui->lblAverageValue->setText(QStringLiteral("--"));
        ui->lblStdValue->setText(QStringLiteral("--"));
        ui->lblFinalResistivity->setText(QStringLiteral("-- ") + UnitOhmCm());
        return;
    }

    double sum = 0.0;
    for(int i = 0; i < values.size(); ++i){
        sum += values.at(i);
    }
    const double average = sum / values.size();

    double variance = 0.0;
    for(int i = 0; i < values.size(); ++i){
        const double diff = values.at(i) - average;
        variance += diff * diff;
    }
    const double stdValue = qSqrt(variance / values.size());

    ui->lblAverageValue->setText(FormatMeasureValue(average, UnitOhmCm()));
    ui->lblStdValue->setText(FormatMeasureValue(stdValue, UnitOhmCm()));
    ui->lblFinalResistivity->setText(FormatMeasureValue(average, UnitOhmCm()));
}

/**
 * @brief Reset_MeasureDisplay
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void Widget::Reset_MeasureDisplay(void)
{
    ui->Label_VoltData->setText(QStringLiteral("-- V"));
    ui->Label_CurrData->setText(QStringLiteral("-- A"));
    ui->lblRealtimeResistance->setText(QStringLiteral("-- ") + UnitOhm());
    ui->Label_ResData->setText(QStringLiteral("-- ") + UnitOhmCm());
    ui->lblAverageValue->setText(QStringLiteral("--"));
    ui->lblStdValue->setText(QStringLiteral("--"));
    ui->lblFinalResistivity->setText(QStringLiteral("-- ") + UnitOhmCm());
    ui->lblMeasureStartTime->setText(QStringLiteral("--"));
    ui->lblDataSavePath->setText(QStringLiteral("--"));
}

/**
 * @brief Add_MeasureValue2Table
 * @author 刘嘉诚
 * @date 2026.06.10
 */
void Widget::Add_MeasureValue2Table(const MeasureValueStruct_TypeDef &value)
{
    const bool isForward = (MeasureState_used.MeasureDirection == MEASUREDIRECTION_FORWARD);
    QTableWidget *debugTable = isForward ? ui->TableWidget_DebugForward : ui->TableWidget_DebugReverse;
    AppendDebugMeasureRow(debugTable,
                          MeasureState_used.cnt_MeasureGroup,
                          MeasureState_used.cnt_MeasureTimes,
                          value);

    const int row = MeasureState_used.cnt_MeasureTimes + 1;
    const int column = MeasureState_used.cnt_MeasureGroup;
    if(row >= 0 && row < ui->TableWidget_f->rowCount() &&
       column >= 0 && column < ui->TableWidget_f->columnCount()){
        QTableWidgetItem *item = EnsureTableItem(ui->TableWidget_f, row, column);
        item->setTextAlignment(Qt::AlignCenter);

        if(isForward){
            item->setText(QStringLiteral("--"));
            item->setData(RoleForwardResistivity, value.Resistivity);
            item->setData(RoleMeanResistivity, QVariant());
        }else{
            double forwardResistivity = 0.0;
            const bool hasForward = ReadFiniteItemData(item, RoleForwardResistivity, &forwardResistivity);
            const bool hasReverse = qIsFinite(value.Resistivity);

            if(hasForward && hasReverse){
                const double meanResistivity = (forwardResistivity + value.Resistivity) / 2.0;
                item->setText(FormatMeasureNumber(meanResistivity));
                item->setData(RoleMeanResistivity, meanResistivity);
            }else if(hasReverse){
                item->setText(FormatMeasureNumber(value.Resistivity));
                item->setData(RoleMeanResistivity, value.Resistivity);
            }else{
                item->setText(QStringLiteral("--"));
                item->setData(RoleMeanResistivity, QVariant());
            }
        }
    }

    MeasureState_used.cnt_MeasureTimes++;
    Update_ResultStatistics();
}
