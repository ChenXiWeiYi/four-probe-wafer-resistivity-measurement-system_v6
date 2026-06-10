#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QPixmap>
#include <QThread>
#include <QTableWidget>
#include <QWidget>

#include "ui_widget.h"

static bool SavePage(Ui::Widget &ui, QWidget &window, QWidget *page, const QString &filePath)
{
    ui.stackedWidgetMain->setCurrentWidget(page);
    qApp->processEvents();
    QThread::msleep(100);
    qApp->processEvents();

    QPixmap pixmap = window.grab();
    const bool saved = pixmap.save(filePath);
    qDebug() << (saved ? "saved" : "failed") << filePath;
    return saved;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString outputDir = QDir::currentPath() + "/ui_previews";
    if(argc > 1){
        outputDir = QString::fromLocal8Bit(argv[1]);
    }

    QDir dir;
    if(!dir.mkpath(outputDir)){
        qWarning() << "failed to create output directory" << outputDir;
        return 1;
    }

    QWidget window;
    Ui::Widget ui;
    ui.setupUi(&window);
    window.setFixedSize(1200, 760);

    ui.Button_SelCOM->setText("COM3");
    ui.lblConnectStatus->setText(QString::fromUtf8("未连接"));
    ui.lblCurrentRange->setText("10 mA");
    ui.lblVoltageRange->setText("10 V");
    ui.lblMeasureMode->setText(QString::fromUtf8("单次测量"));
    ui.lblMeasureState->setText(QString::fromUtf8("空闲"));

    ui.Label_VoltData->setText("0.128 V");
    ui.Label_CurrData->setText("2.500 mA");
    ui.lblRealtimeResistance->setText(QString::fromUtf8("51.2 Ω"));
    ui.Label_ResData->setText(QString::fromUtf8("51.2 Ω·cm"));
    ui.Label_MeasureProgress->setText(QString::fromUtf8("空闲"));
    ui.ProgressBar_MeasureProgress->setValue(0);

    ui.TableWidget_f->setRowCount(8);
    ui.TableWidget_f->setColumnCount(10);
    ui.TableWidget_r->setRowCount(8);
    ui.TableWidget_r->setColumnCount(10);
    for(int i = 0; i < 10; ++i){
        ui.TableWidget_f->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::number(i + 1)));
        ui.TableWidget_r->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::number(i + 1)));
    }
    ui.TableWidget_f->setItem(1, 0, new QTableWidgetItem(QString::fromUtf8("51.12")));
    ui.TableWidget_f->setItem(2, 0, new QTableWidgetItem(QString::fromUtf8("51.25")));
    ui.TableWidget_r->setItem(1, 0, new QTableWidgetItem(QString::fromUtf8("51.05")));
    ui.TableWidget_r->setItem(2, 0, new QTableWidgetItem(QString::fromUtf8("51.30")));

    ui.lblAverageValue->setText(QString::fromUtf8("51.18 Ω·cm"));
    ui.lblStdValue->setText(QString::fromUtf8("0.21 Ω·cm"));
    ui.lblFinalResistivity->setText(QString::fromUtf8("51.18 Ω·cm"));
    ui.lblMeasureStartTime->setText("2026-06-10_14-30-00");
    ui.lblDataSavePath->setText("release/Data/");

    window.show();
    qApp->processEvents();

    bool ok = true;
    ok = SavePage(ui, window, ui.pageExperiment, outputDir + "/01_experiment.png") && ok;
    ok = SavePage(ui, window, ui.pageSample, outputDir + "/02_sample.png") && ok;
    ok = SavePage(ui, window, ui.pageResult, outputDir + "/03_result.png") && ok;
    ok = SavePage(ui, window, ui.pageDebug, outputDir + "/04_debug.png") && ok;

    return ok ? 0 : 2;
}
