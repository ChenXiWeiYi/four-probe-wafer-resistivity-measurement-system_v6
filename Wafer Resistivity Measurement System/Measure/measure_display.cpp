#include "widget.h"
#include "ui_widget.h"
#include <QTableWidget>
#include <QtMath>

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

static void AppendFiniteResistivity(QVector<double> *values, const QVector<MeasureValueStruct_TypeDef> &buffer)
{
    for(int i = 0; i < buffer.size(); ++i){
        const double resistivity = buffer.at(i).Resistivity;
        if(qIsFinite(resistivity)){
            values->append(resistivity);
        }
    }
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
    values.reserve(Buffer_MeasureValue_f.size() + Buffer_MeasureValue_r.size());
    AppendFiniteResistivity(&values, Buffer_MeasureValue_f);
    AppendFiniteResistivity(&values, Buffer_MeasureValue_r);

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
 * @brief Add_Resistivity2Table
 * @author 刘嘉诚
 * @date 2026.06.08
 */
void Widget::Add_Resistivity2Table(double value)
{
    QTableWidget *table = ui->TableWidget_f;
    if(MeasureState_used.MeasureDirection != MEASUREDIRECTION_FORWARD){
        table = ui->TableWidget_r;
    }

    const int row = MeasureState_used.cnt_MeasureTimes + 1;
    const int column = MeasureState_used.cnt_MeasureGroup;
    if(row >= 0 && row < table->rowCount() && column >= 0 && column < table->columnCount()){
        QTableWidgetItem *item = new QTableWidgetItem(FormatMeasureNumber(value));
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(row, column, item);
    }

    MeasureState_used.cnt_MeasureTimes++;
    Update_ResultStatistics();
}
