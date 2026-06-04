/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *Button_SendVoltageRange;
    QPushButton *Button_SendControlVoltage;
    QPushButton *Button_ControlVoltage;
    QPushButton *Button_MeasStart;
    QLineEdit *cin_ControlVoltage;
    QPushButton *Button_SendCurrentPosition;
    QFrame *frame;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QToolButton *Button_VolRange;
    QToolButton *ToolButton_MeasureMode;
    QLabel *Label_name2_3;
    QProgressBar *ProgressBar_Init;
    QLabel *Label_name1;
    QLabel *Label_name2;
    QLabel *Label_name5;
    QSpacerItem *horizontalSpacer_2;
    QFrame *frame_2;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridLayout_4;
    QLabel *Label_name4;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QFrame *frame_3;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QLabel *Label_NameDataVoltage;
    QLabel *Label_ResData;
    QLabel *Label_NameDataCurrent;
    QLabel *Label_CurrData;
    QLabel *Label_VoltData;
    QProgressBar *ProgressBar_MeasureProgress;
    QLabel *Label_name5_2;
    QLabel *Label_NameDataResistivity;
    QLabel *Label_MeasureProgress;
    QWidget *Tab_ParamSetting;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *Label_Name_Temperature;
    QLineEdit *cin_Temperature;
    QLabel *Label_Name_SampleDiameter_3;
    QLabel *Label_Name_SampleDiameter_4;
    QLabel *Label_Name_SampleDiameter_2;
    QLineEdit *cin_ProbeSpacing;
    QPushButton *Button_SelSemiType;
    QLabel *Label_Name_SampleThickness;
    QLabel *Label_Name_SampleThickness_2;
    QLabel *Label_Name_SemiType;
    QLineEdit *cin_SampleDiameter;
    QLabel *Label_Name_SampleDiameter;
    QLabel *Label_Name_FspCorrectionFactor;
    QLineEdit *cin_FspCorrectionFactor;
    QLabel *Label_Name_SampleDiameter_5;
    QLineEdit *cin_CurrErrorBound;
    QLabel *Label_Name_Temperature_4;
    QLabel *Label_Name_SampleDiameter_6;
    QLineEdit *cin_a;
    QLabel *Label_Name_Temperature_3;
    QLabel *Label_Name_Temperature_2;
    QLineEdit *cin_b;
    QLineEdit *cin_Thickness;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QLineEdit *cin_Kp;
    QLineEdit *cin_Ti;
    QLabel *Label_Name_Kp;
    QLabel *Label_Name_Ti;
    QLabel *Label_Current;
    QLabel *Label_Name_Current;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *Label_RE_Current;
    QLabel *Label_Name_Current_2;
    QToolButton *Button_CurrPos;
    QToolButton *ToolButton_ControlAlgo;
    QPushButton *pushButton_3;
    QToolButton *Button_SelCOM;
    QTextEdit *logText_1;
    QPushButton *Button_logText1_CLR;
    QLineEdit *cin_Td;
    QLabel *Label_Name_Td;
    QWidget *tab_54545;
    QTableWidget *TableWidget_f;
    QWidget *tab_6;
    QTableWidget *TableWidget_r;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->setEnabled(true);
        Widget->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        Widget->setMinimumSize(QSize(725, 600));
        Widget->setMaximumSize(QSize(10000, 600));
        Widget->setAutoFillBackground(false);
        tabWidget = new QTabWidget(Widget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 800, 600));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setStyleSheet(QStringLiteral("background-color: rgb(236, 236, 236);"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        Button_SendVoltageRange = new QPushButton(tab);
        Button_SendVoltageRange->setObjectName(QStringLiteral("Button_SendVoltageRange"));
        Button_SendVoltageRange->setGeometry(QRect(260, 340, 111, 28));
        Button_SendControlVoltage = new QPushButton(tab);
        Button_SendControlVoltage->setObjectName(QStringLiteral("Button_SendControlVoltage"));
        Button_SendControlVoltage->setGeometry(QRect(260, 450, 111, 28));
        Button_ControlVoltage = new QPushButton(tab);
        Button_ControlVoltage->setObjectName(QStringLiteral("Button_ControlVoltage"));
        Button_ControlVoltage->setGeometry(QRect(260, 410, 111, 28));
        Button_MeasStart = new QPushButton(tab);
        Button_MeasStart->setObjectName(QStringLiteral("Button_MeasStart"));
        Button_MeasStart->setGeometry(QRect(650, 480, 90, 80));
        Button_MeasStart->setStyleSheet(QLatin1String("border: 2px solid rgb(85, 170, 255);\n"
"font: 12pt \"Consolas\",\"SimHei\";\n"
"background-color: rgb(194, 224, 255);"));
        cin_ControlVoltage = new QLineEdit(tab);
        cin_ControlVoltage->setObjectName(QStringLiteral("cin_ControlVoltage"));
        cin_ControlVoltage->setGeometry(QRect(250, 380, 113, 21));
        Button_SendCurrentPosition = new QPushButton(tab);
        Button_SendCurrentPosition->setObjectName(QStringLiteral("Button_SendCurrentPosition"));
        Button_SendCurrentPosition->setGeometry(QRect(260, 300, 111, 28));
        frame = new QFrame(tab);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 10, 411, 281));
        frame->setStyleSheet(QLatin1String("QFrame{\n"
"	border-radius: 12px;\n"
"	border: 2px solid\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayoutWidget_2 = new QWidget(frame);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 20, 391, 247));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(15);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        Button_VolRange = new QToolButton(gridLayoutWidget_2);
        Button_VolRange->setObjectName(QStringLiteral("Button_VolRange"));
        sizePolicy.setHeightForWidth(Button_VolRange->sizePolicy().hasHeightForWidth());
        Button_VolRange->setSizePolicy(sizePolicy);
        Button_VolRange->setMinimumSize(QSize(230, 50));
        Button_VolRange->setMaximumSize(QSize(230, 50));
        Button_VolRange->setLayoutDirection(Qt::LeftToRight);
        Button_VolRange->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    /* --- \345\216\237\346\234\211\346\240\267\345\274\217 --- */\n"
"    border-color: rgb(100, 100, 100);\n"
"    border-width: 2px;\n"
"    border-style: solid;\n"
"    background-color: rgb(225, 225, 225);\n"
"    font-family: \"Consolas\", \"Courier New\";\n"
"    font-size: 14pt;\n"
"    font-weight: bold;\n"
"    color: black;\n"
"\n"
"    /* --- \346\216\250\350\215\220\344\274\230\345\214\226\346\240\267\345\274\217 --- */\n"
"    padding: 5px 15px;       /* \344\270\212\344\270\213 5px\357\274\214\345\267\246\345\217\263 15px \345\206\205\350\276\271\350\267\235\357\274\214\351\230\262\346\255\242\346\226\207\345\255\227\350\264\264\350\276\271 */\n"
"    border-radius: 4px;      /* 4 \345\203\217\347\264\240\345\234\206\350\247\222\357\274\214\350\256\251\346\214\211\351\222\256\344\270\215\351\202\243\344\271\210\347\224\237\347\241\254 */\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\347\247\273\344\270\212\345\216\273\347\232\204\346\225\210\346\236\234 */\n"
"QToolButton:hover {\n"
""
                        "    background-color: rgb(240, 240, 240); /* \350\203\214\346\231\257\345\217\230\344\272\256\357\274\214\346\217\220\347\244\272\345\217\257\344\272\244\344\272\222 */\n"
"    border-color: rgb(80, 80, 80);        /* \350\276\271\346\241\206\347\250\215\345\276\256\345\212\240\346\267\261 */\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\214\211\344\270\213\345\216\273\347\232\204\346\225\210\346\236\234 */\n"
"QToolButton:pressed {\n"
"    background-color: rgb(200, 200, 200); /* \350\203\214\346\231\257\345\217\230\346\232\227\357\274\214\346\250\241\346\213\237\345\207\271\351\231\267 */\n"
"    border-color: rgb(60, 60, 60);        /* \350\276\271\346\241\206\346\233\264\346\267\261 */\n"
"    \n"
"    /* \346\250\241\346\213\237\346\214\211\351\222\256\350\242\253\346\214\211\344\270\213\347\232\204\344\275\215\347\247\273\346\204\237 (\345\217\257\351\200\211) */\n"
"    padding-top: 6px;     \n"
"    padding-left: 16px;   \n"
"}"));

        gridLayout_2->addWidget(Button_VolRange, 1, 1, 1, 1);

        ToolButton_MeasureMode = new QToolButton(gridLayoutWidget_2);
        ToolButton_MeasureMode->setObjectName(QStringLiteral("ToolButton_MeasureMode"));
        sizePolicy.setHeightForWidth(ToolButton_MeasureMode->sizePolicy().hasHeightForWidth());
        ToolButton_MeasureMode->setSizePolicy(sizePolicy);
        ToolButton_MeasureMode->setMinimumSize(QSize(230, 50));
        ToolButton_MeasureMode->setMaximumSize(QSize(230, 50));
        ToolButton_MeasureMode->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    /* --- \345\216\237\346\234\211\346\240\267\345\274\217 --- */\n"
"    border-color: rgb(100, 100, 100);\n"
"    border-width: 2px;\n"
"    border-style: solid;\n"
"    background-color: rgb(225, 225, 225);\n"
"    font-family: \"Consolas\", \"Courier New\";\n"
"    font-size: 14pt;\n"
"    font-weight: bold;\n"
"    color: black;\n"
"\n"
"    /* --- \346\216\250\350\215\220\344\274\230\345\214\226\346\240\267\345\274\217 --- */\n"
"    padding: 5px 15px;       /* \344\270\212\344\270\213 5px\357\274\214\345\267\246\345\217\263 15px \345\206\205\350\276\271\350\267\235\357\274\214\351\230\262\346\255\242\346\226\207\345\255\227\350\264\264\350\276\271 */\n"
"    border-radius: 4px;      /* 4 \345\203\217\347\264\240\345\234\206\350\247\222\357\274\214\350\256\251\346\214\211\351\222\256\344\270\215\351\202\243\344\271\210\347\224\237\347\241\254 */\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\347\247\273\344\270\212\345\216\273\347\232\204\346\225\210\346\236\234 */\n"
"QToolButton:hover {\n"
""
                        "    background-color: rgb(240, 240, 240); /* \350\203\214\346\231\257\345\217\230\344\272\256\357\274\214\346\217\220\347\244\272\345\217\257\344\272\244\344\272\222 */\n"
"    border-color: rgb(80, 80, 80);        /* \350\276\271\346\241\206\347\250\215\345\276\256\345\212\240\346\267\261 */\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\214\211\344\270\213\345\216\273\347\232\204\346\225\210\346\236\234 */\n"
"QToolButton:pressed {\n"
"    background-color: rgb(200, 200, 200); /* \350\203\214\346\231\257\345\217\230\346\232\227\357\274\214\346\250\241\346\213\237\345\207\271\351\231\267 */\n"
"    border-color: rgb(60, 60, 60);        /* \350\276\271\346\241\206\346\233\264\346\267\261 */\n"
"    \n"
"    /* \346\250\241\346\213\237\346\214\211\351\222\256\350\242\253\346\214\211\344\270\213\347\232\204\344\275\215\347\247\273\346\204\237 (\345\217\257\351\200\211) */\n"
"    padding-top: 6px;     \n"
"    padding-left: 16px;   \n"
"}"));

        gridLayout_2->addWidget(ToolButton_MeasureMode, 2, 1, 1, 1);

        Label_name2_3 = new QLabel(gridLayoutWidget_2);
        Label_name2_3->setObjectName(QStringLiteral("Label_name2_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(Label_name2_3->sizePolicy().hasHeightForWidth());
        Label_name2_3->setSizePolicy(sizePolicy2);
        Label_name2_3->setMinimumSize(QSize(0, 0));
        Label_name2_3->setMaximumSize(QSize(300, 50));
        Label_name2_3->setStyleSheet(QLatin1String("border: 0px;\n"
"font: 14pt \"Consolas\",\"SimHei\";\n"
"background-color: none;"));
        Label_name2_3->setLineWidth(0);
        Label_name2_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(Label_name2_3, 2, 0, 1, 1);

        ProgressBar_Init = new QProgressBar(gridLayoutWidget_2);
        ProgressBar_Init->setObjectName(QStringLiteral("ProgressBar_Init"));
        sizePolicy.setHeightForWidth(ProgressBar_Init->sizePolicy().hasHeightForWidth());
        ProgressBar_Init->setSizePolicy(sizePolicy);
        ProgressBar_Init->setMinimumSize(QSize(230, 0));
        ProgressBar_Init->setMaximumSize(QSize(230, 40));
        ProgressBar_Init->setStyleSheet(QString::fromUtf8("/* \346\241\206 */\n"
"border-color: rgb(100, 100, 100);\n"
"border-width: 2px;\n"
"border-style: solid;\n"
"/* \350\203\214\346\231\257 */\n"
"background-color: rgb(225, 225, 225);\n"
"/* \345\255\227 */\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;\n"
"color: black;"));
        ProgressBar_Init->setValue(24);
        ProgressBar_Init->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(ProgressBar_Init, 3, 1, 1, 1);

        Label_name1 = new QLabel(gridLayoutWidget_2);
        Label_name1->setObjectName(QStringLiteral("Label_name1"));
        sizePolicy2.setHeightForWidth(Label_name1->sizePolicy().hasHeightForWidth());
        Label_name1->setSizePolicy(sizePolicy2);
        Label_name1->setMinimumSize(QSize(0, 0));
        Label_name1->setMaximumSize(QSize(300, 50));
        Label_name1->setStyleSheet(QLatin1String("border: 0px;\n"
"font: 14pt \"Consolas\",\"SimHei\";\n"
"background-color: none;"));
        Label_name1->setLineWidth(0);
        Label_name1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(Label_name1, 0, 0, 1, 1);

        Label_name2 = new QLabel(gridLayoutWidget_2);
        Label_name2->setObjectName(QStringLiteral("Label_name2"));
        sizePolicy2.setHeightForWidth(Label_name2->sizePolicy().hasHeightForWidth());
        Label_name2->setSizePolicy(sizePolicy2);
        Label_name2->setMinimumSize(QSize(0, 0));
        Label_name2->setMaximumSize(QSize(300, 50));
        Label_name2->setStyleSheet(QLatin1String("border: 0px;\n"
"font: 14pt \"Consolas\",\"SimHei\";\n"
"background-color: none;"));
        Label_name2->setLineWidth(0);
        Label_name2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(Label_name2, 1, 0, 1, 1);

        Label_name5 = new QLabel(gridLayoutWidget_2);
        Label_name5->setObjectName(QStringLiteral("Label_name5"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(Label_name5->sizePolicy().hasHeightForWidth());
        Label_name5->setSizePolicy(sizePolicy3);
        Label_name5->setMinimumSize(QSize(0, 50));
        Label_name5->setMaximumSize(QSize(300, 50));
        Label_name5->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font: 14pt bold \"Consolas\",\"SimHei\";"));
        Label_name5->setLineWidth(0);
        Label_name5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(Label_name5, 3, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        frame_2 = new QFrame(tab);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(430, 10, 331, 81));
        frame_2->setStyleSheet(QLatin1String("QFrame{\n"
"	border-radius: 12px;\n"
"	border: 2px solid\n"
"}"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayoutWidget_4 = new QWidget(frame_2);
        gridLayoutWidget_4->setObjectName(QStringLiteral("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(20, 10, 303, 59));
        gridLayout_4 = new QGridLayout(gridLayoutWidget_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        Label_name4 = new QLabel(gridLayoutWidget_4);
        Label_name4->setObjectName(QStringLiteral("Label_name4"));
        sizePolicy3.setHeightForWidth(Label_name4->sizePolicy().hasHeightForWidth());
        Label_name4->setSizePolicy(sizePolicy3);
        Label_name4->setMinimumSize(QSize(0, 50));
        Label_name4->setMaximumSize(QSize(1000000, 50));
        Label_name4->setStyleSheet(QLatin1String("border: 0px;\n"
"font: 14pt \"Consolas\",\"SimHei\";\n"
"background-color: none;"));
        Label_name4->setLineWidth(0);
        Label_name4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(Label_name4, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_2, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_3, 0, 1, 1, 1);

        frame_3 = new QFrame(tab);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(430, 100, 331, 321));
        frame_3->setStyleSheet(QLatin1String("QFrame{\n"
"	border-radius: 12px;\n"
"	border: 2px solid\n"
"}"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayoutWidget_3 = new QWidget(frame_3);
        gridLayoutWidget_3->setObjectName(QStringLiteral("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(10, 20, 309, 280));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        Label_NameDataVoltage = new QLabel(gridLayoutWidget_3);
        Label_NameDataVoltage->setObjectName(QStringLiteral("Label_NameDataVoltage"));
        sizePolicy.setHeightForWidth(Label_NameDataVoltage->sizePolicy().hasHeightForWidth());
        Label_NameDataVoltage->setSizePolicy(sizePolicy);
        Label_NameDataVoltage->setMinimumSize(QSize(120, 0));
        Label_NameDataVoltage->setMaximumSize(QSize(16777215, 40));
        Label_NameDataVoltage->setStyleSheet(QLatin1String("border: 0px;\n"
"font: 14pt \"Consolas\",\"SimHei\";\n"
"background-color: none;"));
        Label_NameDataVoltage->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(Label_NameDataVoltage, 0, 0, 1, 1);

        Label_ResData = new QLabel(gridLayoutWidget_3);
        Label_ResData->setObjectName(QStringLiteral("Label_ResData"));
        Label_ResData->setEnabled(true);
        sizePolicy.setHeightForWidth(Label_ResData->sizePolicy().hasHeightForWidth());
        Label_ResData->setSizePolicy(sizePolicy);
        Label_ResData->setMinimumSize(QSize(150, 50));
        Label_ResData->setStyleSheet(QLatin1String("font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;\n"
"color: black;\n"
"border: none;"));

        gridLayout_3->addWidget(Label_ResData, 2, 1, 1, 1);

        Label_NameDataCurrent = new QLabel(gridLayoutWidget_3);
        Label_NameDataCurrent->setObjectName(QStringLiteral("Label_NameDataCurrent"));
        sizePolicy.setHeightForWidth(Label_NameDataCurrent->sizePolicy().hasHeightForWidth());
        Label_NameDataCurrent->setSizePolicy(sizePolicy);
        Label_NameDataCurrent->setMinimumSize(QSize(120, 0));
        Label_NameDataCurrent->setMaximumSize(QSize(16777215, 40));
        Label_NameDataCurrent->setStyleSheet(QLatin1String("border: 0px;\n"
"font: 14pt \"Consolas\",\"SimHei\";\n"
"background-color: none;"));
        Label_NameDataCurrent->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(Label_NameDataCurrent, 1, 0, 1, 1);

        Label_CurrData = new QLabel(gridLayoutWidget_3);
        Label_CurrData->setObjectName(QStringLiteral("Label_CurrData"));
        Label_CurrData->setEnabled(true);
        sizePolicy.setHeightForWidth(Label_CurrData->sizePolicy().hasHeightForWidth());
        Label_CurrData->setSizePolicy(sizePolicy);
        Label_CurrData->setMinimumSize(QSize(150, 50));
        Label_CurrData->setStyleSheet(QLatin1String("font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;\n"
"color: black;\n"
"border: none;"));

        gridLayout_3->addWidget(Label_CurrData, 0, 1, 1, 1);

        Label_VoltData = new QLabel(gridLayoutWidget_3);
        Label_VoltData->setObjectName(QStringLiteral("Label_VoltData"));
        Label_VoltData->setEnabled(true);
        sizePolicy.setHeightForWidth(Label_VoltData->sizePolicy().hasHeightForWidth());
        Label_VoltData->setSizePolicy(sizePolicy);
        Label_VoltData->setMinimumSize(QSize(150, 50));
        Label_VoltData->setStyleSheet(QLatin1String("font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;\n"
"color: black;\n"
"border: none;"));

        gridLayout_3->addWidget(Label_VoltData, 1, 1, 1, 1);

        ProgressBar_MeasureProgress = new QProgressBar(gridLayoutWidget_3);
        ProgressBar_MeasureProgress->setObjectName(QStringLiteral("ProgressBar_MeasureProgress"));
        sizePolicy.setHeightForWidth(ProgressBar_MeasureProgress->sizePolicy().hasHeightForWidth());
        ProgressBar_MeasureProgress->setSizePolicy(sizePolicy);
        ProgressBar_MeasureProgress->setMinimumSize(QSize(150, 50));
        ProgressBar_MeasureProgress->setMaximumSize(QSize(150, 50));
        ProgressBar_MeasureProgress->setStyleSheet(QString::fromUtf8("/* \346\241\206 */\n"
"border-color: rgb(100, 100, 100);\n"
"border-width: 2px;\n"
"border-style: solid;\n"
"/* \350\203\214\346\231\257 */\n"
"background-color: rgb(225, 225, 225);\n"
"/* \345\255\227 */\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;\n"
"color: black;"));
        ProgressBar_MeasureProgress->setValue(24);
        ProgressBar_MeasureProgress->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(ProgressBar_MeasureProgress, 3, 1, 1, 1);

        Label_name5_2 = new QLabel(gridLayoutWidget_3);
        Label_name5_2->setObjectName(QStringLiteral("Label_name5_2"));
        sizePolicy3.setHeightForWidth(Label_name5_2->sizePolicy().hasHeightForWidth());
        Label_name5_2->setSizePolicy(sizePolicy3);
        Label_name5_2->setMinimumSize(QSize(120, 50));
        Label_name5_2->setMaximumSize(QSize(300, 50));
        Label_name5_2->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font: 14pt bold \"Consolas\",\"SimHei\";"));
        Label_name5_2->setLineWidth(0);
        Label_name5_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(Label_name5_2, 3, 0, 1, 1);

        Label_NameDataResistivity = new QLabel(gridLayoutWidget_3);
        Label_NameDataResistivity->setObjectName(QStringLiteral("Label_NameDataResistivity"));
        sizePolicy.setHeightForWidth(Label_NameDataResistivity->sizePolicy().hasHeightForWidth());
        Label_NameDataResistivity->setSizePolicy(sizePolicy);
        Label_NameDataResistivity->setMinimumSize(QSize(120, 0));
        Label_NameDataResistivity->setMaximumSize(QSize(16777215, 40));
        Label_NameDataResistivity->setStyleSheet(QLatin1String("border: 0px;\n"
"font: 14pt \"Consolas\",\"SimHei\";\n"
"background-color: none;"));
        Label_NameDataResistivity->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(Label_NameDataResistivity, 2, 0, 1, 1);

        Label_MeasureProgress = new QLabel(gridLayoutWidget_3);
        Label_MeasureProgress->setObjectName(QStringLiteral("Label_MeasureProgress"));
        sizePolicy3.setHeightForWidth(Label_MeasureProgress->sizePolicy().hasHeightForWidth());
        Label_MeasureProgress->setSizePolicy(sizePolicy3);
        Label_MeasureProgress->setMinimumSize(QSize(120, 50));
        Label_MeasureProgress->setMaximumSize(QSize(300, 50));
        Label_MeasureProgress->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font: 14pt bold \"Consolas\",\"SimHei\";"));
        Label_MeasureProgress->setLineWidth(0);
        Label_MeasureProgress->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(Label_MeasureProgress, 4, 1, 1, 1);

        tabWidget->addTab(tab, QString());
        Tab_ParamSetting = new QWidget();
        Tab_ParamSetting->setObjectName(QStringLiteral("Tab_ParamSetting"));
        Tab_ParamSetting->setStyleSheet(QStringLiteral(""));
        gridLayoutWidget = new QWidget(Tab_ParamSetting);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(30, 10, 321, 499));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(5);
        gridLayout->setVerticalSpacing(15);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        Label_Name_Temperature = new QLabel(gridLayoutWidget);
        Label_Name_Temperature->setObjectName(QStringLiteral("Label_Name_Temperature"));
        Label_Name_Temperature->setMinimumSize(QSize(130, 0));
        Label_Name_Temperature->setMaximumSize(QSize(130, 50));
        Label_Name_Temperature->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;"));
        Label_Name_Temperature->setLineWidth(0);
        Label_Name_Temperature->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(Label_Name_Temperature, 5, 0, 1, 1);

        cin_Temperature = new QLineEdit(gridLayoutWidget);
        cin_Temperature->setObjectName(QStringLiteral("cin_Temperature"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(cin_Temperature->sizePolicy().hasHeightForWidth());
        cin_Temperature->setSizePolicy(sizePolicy4);
        cin_Temperature->setMinimumSize(QSize(120, 40));
        cin_Temperature->setMaximumSize(QSize(120, 40));
        cin_Temperature->setStyleSheet(QString::fromUtf8("/* \346\241\206 */\n"
"border-color: rgb(100, 100, 100);\n"
"border-width: 2px;\n"
"border-style: solid;\n"
"border-radius: 4px;\n"
"/* \350\203\214\346\231\257 */\n"
"background-color: rgb(255, 255, 255);\n"
"/* \345\255\227 */\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;\n"
"color: black;"));
        cin_Temperature->setAlignment(Qt::AlignCenter);
        cin_Temperature->setProperty("fixedSize", QVariant(QSize(70, 23)));

        gridLayout->addWidget(cin_Temperature, 5, 1, 1, 1);

        Label_Name_SampleDiameter_3 = new QLabel(gridLayoutWidget);
        Label_Name_SampleDiameter_3->setObjectName(QStringLiteral("Label_Name_SampleDiameter_3"));
        sizePolicy2.setHeightForWidth(Label_Name_SampleDiameter_3->sizePolicy().hasHeightForWidth());
        Label_Name_SampleDiameter_3->setSizePolicy(sizePolicy2);
        Label_Name_SampleDiameter_3->setMinimumSize(QSize(30, 0));
        Label_Name_SampleDiameter_3->setMaximumSize(QSize(30, 16777215));
        Label_Name_SampleDiameter_3->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;"));
        Label_Name_SampleDiameter_3->setLineWidth(0);
        Label_Name_SampleDiameter_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(Label_Name_SampleDiameter_3, 3, 2, 1, 1);

        Label_Name_SampleDiameter_4 = new QLabel(gridLayoutWidget);
        Label_Name_SampleDiameter_4->setObjectName(QStringLiteral("Label_Name_SampleDiameter_4"));
        sizePolicy2.setHeightForWidth(Label_Name_SampleDiameter_4->sizePolicy().hasHeightForWidth());
        Label_Name_SampleDiameter_4->setSizePolicy(sizePolicy2);
        Label_Name_SampleDiameter_4->setMinimumSize(QSize(30, 0));
        Label_Name_SampleDiameter_4->setMaximumSize(QSize(30, 16777215));
        Label_Name_SampleDiameter_4->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;"));
        Label_Name_SampleDiameter_4->setLineWidth(0);
        Label_Name_SampleDiameter_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(Label_Name_SampleDiameter_4, 4, 2, 1, 1);

        Label_Name_SampleDiameter_2 = new QLabel(gridLayoutWidget);
        Label_Name_SampleDiameter_2->setObjectName(QStringLiteral("Label_Name_SampleDiameter_2"));
        sizePolicy2.setHeightForWidth(Label_Name_SampleDiameter_2->sizePolicy().hasHeightForWidth());
        Label_Name_SampleDiameter_2->setSizePolicy(sizePolicy2);
        Label_Name_SampleDiameter_2->setMinimumSize(QSize(30, 0));
        Label_Name_SampleDiameter_2->setMaximumSize(QSize(30, 16777215));
        Label_Name_SampleDiameter_2->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;"));
        Label_Name_SampleDiameter_2->setLineWidth(0);
        Label_Name_SampleDiameter_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(Label_Name_SampleDiameter_2, 2, 2, 1, 1);

        cin_ProbeSpacing = new QLineEdit(gridLayoutWidget);
        cin_ProbeSpacing->setObjectName(QStringLiteral("cin_ProbeSpacing"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(cin_ProbeSpacing->sizePolicy().hasHeightForWidth());
        cin_ProbeSpacing->setSizePolicy(sizePolicy5);
        cin_ProbeSpacing->setMinimumSize(QSize(120, 40));
        cin_ProbeSpacing->setMaximumSize(QSize(120, 40));
        cin_ProbeSpacing->setStyleSheet(QString::fromUtf8("/* \346\241\206 */\n"
"border-color: rgb(100, 100, 100);\n"
"border-width: 2px;\n"
"border-style: solid;\n"
"border-radius: 4px;\n"
"/* \350\203\214\346\231\257 */\n"
"background-color: rgb(255, 255, 255);\n"
"/* \345\255\227 */\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;\n"
"color: black;"));
        cin_ProbeSpacing->setAlignment(Qt::AlignCenter);
        cin_ProbeSpacing->setProperty("fixedSize", QVariant(QSize(70, 23)));

        gridLayout->addWidget(cin_ProbeSpacing, 3, 1, 1, 1);

        Button_SelSemiType = new QPushButton(gridLayoutWidget);
        Button_SelSemiType->setObjectName(QStringLiteral("Button_SelSemiType"));
        sizePolicy4.setHeightForWidth(Button_SelSemiType->sizePolicy().hasHeightForWidth());
        Button_SelSemiType->setSizePolicy(sizePolicy4);
        Button_SelSemiType->setMinimumSize(QSize(120, 40));
        Button_SelSemiType->setMaximumSize(QSize(120, 40));
        Button_SelSemiType->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    /* --- \345\216\237\346\234\211\346\240\267\345\274\217 --- */\n"
"    border-color: rgb(100, 100, 100);\n"
"    border-width: 2px;\n"
"    border-style: solid;\n"
"    background-color: rgb(215, 215, 215);\n"
"    font-family: \"Consolas\", \"Courier New\";\n"
"    font-size: 14pt;\n"
"    font-weight: bold;\n"
"    color: black;\n"
"\n"
"    /* --- \346\216\250\350\215\220\344\274\230\345\214\226\346\240\267\345\274\217 --- */\n"
"    padding: 5px 15px;       /* \344\270\212\344\270\213 5px\357\274\214\345\267\246\345\217\263 15px \345\206\205\350\276\271\350\267\235\357\274\214\351\230\262\346\255\242\346\226\207\345\255\227\350\264\264\350\276\271 */\n"
"    border-radius: 4px;      /* 4 \345\203\217\347\264\240\345\234\206\350\247\222\357\274\214\350\256\251\346\214\211\351\222\256\344\270\215\351\202\243\344\271\210\347\224\237\347\241\254 */\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\347\247\273\344\270\212\345\216\273\347\232\204\346\225\210\346\236\234 */\n"
"QPushButton:hover {\n"
""
                        "    background-color: rgb(230, 230, 230); /* \350\203\214\346\231\257\345\217\230\344\272\256\357\274\214\346\217\220\347\244\272\345\217\257\344\272\244\344\272\222 */\n"
"    border-color: rgb(80, 80, 80);        /* \350\276\271\346\241\206\347\250\215\345\276\256\345\212\240\346\267\261 */\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\214\211\344\270\213\345\216\273\347\232\204\346\225\210\346\236\234 */\n"
"QPushButton:pressed {\n"
"    background-color: rgb(190, 190, 190); /* \350\203\214\346\231\257\345\217\230\346\232\227\357\274\214\346\250\241\346\213\237\345\207\271\351\231\267 */\n"
"    border-color: rgb(60, 60, 60);        /* \350\276\271\346\241\206\346\233\264\346\267\261 */\n"
"    \n"
"    /* \346\250\241\346\213\237\346\214\211\351\222\256\350\242\253\346\214\211\344\270\213\347\232\204\344\275\215\347\247\273\346\204\237 (\345\217\257\351\200\211) */\n"
"    padding-top: 6px;     \n"
"    padding-left: 16px;   \n"
"}"));
        Button_SelSemiType->setProperty("fixedSize", QVariant(QSize(100, 50)));

        gridLayout->addWidget(Button_SelSemiType, 1, 1, 1, 1);

        Label_Name_SampleThickness = new QLabel(gridLayoutWidget);
        Label_Name_SampleThickness->setObjectName(QStringLiteral("Label_Name_SampleThickness"));
        sizePolicy2.setHeightForWidth(Label_Name_SampleThickness->sizePolicy().hasHeightForWidth());
        Label_Name_SampleThickness->setSizePolicy(sizePolicy2);
        Label_Name_SampleThickness->setMinimumSize(QSize(130, 0));
        Label_Name_SampleThickness->setMaximumSize(QSize(130, 16777215));
        Label_Name_SampleThickness->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;"));
        Label_Name_SampleThickness->setLineWidth(0);
        Label_Name_SampleThickness->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(Label_Name_SampleThickness, 4, 0, 1, 1);

        Label_Name_SampleThickness_2 = new QLabel(gridLayoutWidget);
        Label_Name_SampleThickness_2->setObjectName(QStringLiteral("Label_Name_SampleThickness_2"));
        sizePolicy3.setHeightForWidth(Label_Name_SampleThickness_2->sizePolicy().hasHeightForWidth());
        Label_Name_SampleThickness_2->setSizePolicy(sizePolicy3);
        Label_Name_SampleThickness_2->setMinimumSize(QSize(130, 0));
        Label_Name_SampleThickness_2->setMaximumSize(QSize(130, 16777215));
        Label_Name_SampleThickness_2->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;"));
        Label_Name_SampleThickness_2->setLineWidth(0);
        Label_Name_SampleThickness_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(Label_Name_SampleThickness_2, 3, 0, 1, 1);

        Label_Name_SemiType = new QLabel(gridLayoutWidget);
        Label_Name_SemiType->setObjectName(QStringLiteral("Label_Name_SemiType"));
        Label_Name_SemiType->setMinimumSize(QSize(130, 0));
        Label_Name_SemiType->setMaximumSize(QSize(130, 16777215));
        Label_Name_SemiType->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;"));
        Label_Name_SemiType->setLineWidth(0);
        Label_Name_SemiType->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(Label_Name_SemiType, 1, 0, 1, 1);

        cin_SampleDiameter = new QLineEdit(gridLayoutWidget);
        cin_SampleDiameter->setObjectName(QStringLiteral("cin_SampleDiameter"));
        sizePolicy4.setHeightForWidth(cin_SampleDiameter->sizePolicy().hasHeightForWidth());
        cin_SampleDiameter->setSizePolicy(sizePolicy4);
        cin_SampleDiameter->setMinimumSize(QSize(120, 40));
        cin_SampleDiameter->setMaximumSize(QSize(120, 40));
        cin_SampleDiameter->setStyleSheet(QString::fromUtf8("/* \346\241\206 */\n"
"border-color: rgb(100, 100, 100);\n"
"border-width: 2px;\n"
"border-style: solid;\n"
"border-radius: 4px;\n"
"/* \350\203\214\346\231\257 */\n"
"background-color: rgb(255, 255, 255);\n"
"/* \345\255\227 */\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;\n"
"color: black;"));
        cin_SampleDiameter->setAlignment(Qt::AlignCenter);
        cin_SampleDiameter->setProperty("fixedSize", QVariant(QSize(70, 23)));

        gridLayout->addWidget(cin_SampleDiameter, 2, 1, 1, 1);

        Label_Name_SampleDiameter = new QLabel(gridLayoutWidget);
        Label_Name_SampleDiameter->setObjectName(QStringLiteral("Label_Name_SampleDiameter"));
        sizePolicy3.setHeightForWidth(Label_Name_SampleDiameter->sizePolicy().hasHeightForWidth());
        Label_Name_SampleDiameter->setSizePolicy(sizePolicy3);
        Label_Name_SampleDiameter->setMinimumSize(QSize(130, 0));
        Label_Name_SampleDiameter->setMaximumSize(QSize(130, 50));
        Label_Name_SampleDiameter->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;"));
        Label_Name_SampleDiameter->setLineWidth(0);
        Label_Name_SampleDiameter->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(Label_Name_SampleDiameter, 2, 0, 1, 1);

        Label_Name_FspCorrectionFactor = new QLabel(gridLayoutWidget);
        Label_Name_FspCorrectionFactor->setObjectName(QStringLiteral("Label_Name_FspCorrectionFactor"));
        Label_Name_FspCorrectionFactor->setMinimumSize(QSize(130, 0));
        Label_Name_FspCorrectionFactor->setMaximumSize(QSize(130, 16777215));
        Label_Name_FspCorrectionFactor->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;"));
        Label_Name_FspCorrectionFactor->setLineWidth(0);
        Label_Name_FspCorrectionFactor->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(Label_Name_FspCorrectionFactor, 0, 0, 1, 1);

        cin_FspCorrectionFactor = new QLineEdit(gridLayoutWidget);
        cin_FspCorrectionFactor->setObjectName(QStringLiteral("cin_FspCorrectionFactor"));
        sizePolicy5.setHeightForWidth(cin_FspCorrectionFactor->sizePolicy().hasHeightForWidth());
        cin_FspCorrectionFactor->setSizePolicy(sizePolicy5);
        cin_FspCorrectionFactor->setMinimumSize(QSize(120, 40));
        cin_FspCorrectionFactor->setMaximumSize(QSize(120, 40));
        cin_FspCorrectionFactor->setStyleSheet(QString::fromUtf8("/* \346\241\206 */\n"
"border-color: rgb(100, 100, 100);\n"
"border-width: 2px;\n"
"border-style: solid;\n"
"border-radius: 4px;\n"
"/* \350\203\214\346\231\257 */\n"
"background-color: rgb(255, 255, 255);\n"
"/* \345\255\227 */\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;\n"
"color: black;"));
        cin_FspCorrectionFactor->setAlignment(Qt::AlignCenter);
        cin_FspCorrectionFactor->setProperty("fixedSize", QVariant(QSize(70, 23)));

        gridLayout->addWidget(cin_FspCorrectionFactor, 0, 1, 1, 1);

        Label_Name_SampleDiameter_5 = new QLabel(gridLayoutWidget);
        Label_Name_SampleDiameter_5->setObjectName(QStringLiteral("Label_Name_SampleDiameter_5"));
        sizePolicy2.setHeightForWidth(Label_Name_SampleDiameter_5->sizePolicy().hasHeightForWidth());
        Label_Name_SampleDiameter_5->setSizePolicy(sizePolicy2);
        Label_Name_SampleDiameter_5->setMinimumSize(QSize(30, 0));
        Label_Name_SampleDiameter_5->setMaximumSize(QSize(30, 16777215));
        Label_Name_SampleDiameter_5->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;"));
        Label_Name_SampleDiameter_5->setLineWidth(0);
        Label_Name_SampleDiameter_5->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(Label_Name_SampleDiameter_5, 5, 2, 1, 1);

        cin_CurrErrorBound = new QLineEdit(gridLayoutWidget);
        cin_CurrErrorBound->setObjectName(QStringLiteral("cin_CurrErrorBound"));
        QSizePolicy sizePolicy6(QSizePolicy::Ignored, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(cin_CurrErrorBound->sizePolicy().hasHeightForWidth());
        cin_CurrErrorBound->setSizePolicy(sizePolicy6);
        cin_CurrErrorBound->setMinimumSize(QSize(120, 40));
        cin_CurrErrorBound->setMaximumSize(QSize(120, 40));
        cin_CurrErrorBound->setStyleSheet(QString::fromUtf8("/* \346\241\206 */\n"
"border-color: rgb(100, 100, 100);\n"
"border-width: 2px;\n"
"border-style: solid;\n"
"border-radius: 4px;\n"
"/* \350\203\214\346\231\257 */\n"
"background-color: rgb(255, 255, 255);\n"
"/* \345\255\227 */\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;\n"
"color: black;"));
        cin_CurrErrorBound->setAlignment(Qt::AlignCenter);
        cin_CurrErrorBound->setProperty("fixedSize", QVariant(QSize(70, 23)));

        gridLayout->addWidget(cin_CurrErrorBound, 8, 1, 1, 1);

        Label_Name_Temperature_4 = new QLabel(gridLayoutWidget);
        Label_Name_Temperature_4->setObjectName(QStringLiteral("Label_Name_Temperature_4"));
        Label_Name_Temperature_4->setMinimumSize(QSize(130, 0));
        Label_Name_Temperature_4->setMaximumSize(QSize(130, 50));
        Label_Name_Temperature_4->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;"));
        Label_Name_Temperature_4->setLineWidth(0);
        Label_Name_Temperature_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(Label_Name_Temperature_4, 8, 0, 1, 1);

        Label_Name_SampleDiameter_6 = new QLabel(gridLayoutWidget);
        Label_Name_SampleDiameter_6->setObjectName(QStringLiteral("Label_Name_SampleDiameter_6"));
        sizePolicy2.setHeightForWidth(Label_Name_SampleDiameter_6->sizePolicy().hasHeightForWidth());
        Label_Name_SampleDiameter_6->setSizePolicy(sizePolicy2);
        Label_Name_SampleDiameter_6->setMinimumSize(QSize(30, 0));
        Label_Name_SampleDiameter_6->setMaximumSize(QSize(30, 16777215));
        Label_Name_SampleDiameter_6->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;"));
        Label_Name_SampleDiameter_6->setLineWidth(0);
        Label_Name_SampleDiameter_6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(Label_Name_SampleDiameter_6, 8, 2, 1, 1);

        cin_a = new QLineEdit(gridLayoutWidget);
        cin_a->setObjectName(QStringLiteral("cin_a"));
        sizePolicy6.setHeightForWidth(cin_a->sizePolicy().hasHeightForWidth());
        cin_a->setSizePolicy(sizePolicy6);
        cin_a->setMinimumSize(QSize(120, 40));
        cin_a->setMaximumSize(QSize(120, 40));
        cin_a->setStyleSheet(QString::fromUtf8("/* \346\241\206 */\n"
"border-color: rgb(100, 100, 100);\n"
"border-width: 2px;\n"
"border-style: solid;\n"
"border-radius: 4px;\n"
"/* \350\203\214\346\231\257 */\n"
"background-color: rgb(255, 255, 255);\n"
"/* \345\255\227 */\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;\n"
"color: black;"));
        cin_a->setAlignment(Qt::AlignCenter);
        cin_a->setProperty("fixedSize", QVariant(QSize(70, 23)));

        gridLayout->addWidget(cin_a, 6, 1, 1, 1);

        Label_Name_Temperature_3 = new QLabel(gridLayoutWidget);
        Label_Name_Temperature_3->setObjectName(QStringLiteral("Label_Name_Temperature_3"));
        Label_Name_Temperature_3->setMinimumSize(QSize(130, 0));
        Label_Name_Temperature_3->setMaximumSize(QSize(130, 50));
        Label_Name_Temperature_3->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;"));
        Label_Name_Temperature_3->setLineWidth(0);
        Label_Name_Temperature_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(Label_Name_Temperature_3, 7, 0, 1, 1);

        Label_Name_Temperature_2 = new QLabel(gridLayoutWidget);
        Label_Name_Temperature_2->setObjectName(QStringLiteral("Label_Name_Temperature_2"));
        Label_Name_Temperature_2->setMinimumSize(QSize(130, 0));
        Label_Name_Temperature_2->setMaximumSize(QSize(130, 50));
        Label_Name_Temperature_2->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;"));
        Label_Name_Temperature_2->setLineWidth(0);
        Label_Name_Temperature_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(Label_Name_Temperature_2, 6, 0, 1, 1);

        cin_b = new QLineEdit(gridLayoutWidget);
        cin_b->setObjectName(QStringLiteral("cin_b"));
        sizePolicy6.setHeightForWidth(cin_b->sizePolicy().hasHeightForWidth());
        cin_b->setSizePolicy(sizePolicy6);
        cin_b->setMinimumSize(QSize(120, 40));
        cin_b->setMaximumSize(QSize(120, 40));
        cin_b->setStyleSheet(QString::fromUtf8("/* \346\241\206 */\n"
"border-color: rgb(100, 100, 100);\n"
"border-width: 2px;\n"
"border-style: solid;\n"
"border-radius: 4px;\n"
"/* \350\203\214\346\231\257 */\n"
"background-color: rgb(255, 255, 255);\n"
"/* \345\255\227 */\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;\n"
"color: black;"));
        cin_b->setAlignment(Qt::AlignCenter);
        cin_b->setProperty("fixedSize", QVariant(QSize(70, 23)));

        gridLayout->addWidget(cin_b, 7, 1, 1, 1);

        cin_Thickness = new QLineEdit(gridLayoutWidget);
        cin_Thickness->setObjectName(QStringLiteral("cin_Thickness"));
        sizePolicy4.setHeightForWidth(cin_Thickness->sizePolicy().hasHeightForWidth());
        cin_Thickness->setSizePolicy(sizePolicy4);
        cin_Thickness->setMinimumSize(QSize(120, 40));
        cin_Thickness->setMaximumSize(QSize(120, 40));
        cin_Thickness->setStyleSheet(QString::fromUtf8("/* \346\241\206 */\n"
"border-color: rgb(100, 100, 100);\n"
"border-width: 2px;\n"
"border-style: solid;\n"
"border-radius: 4px;\n"
"/* \350\203\214\346\231\257 */\n"
"background-color: rgb(255, 255, 255);\n"
"/* \345\255\227 */\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;\n"
"color: black;"));
        cin_Thickness->setAlignment(Qt::AlignCenter);
        cin_Thickness->setProperty("fixedSize", QVariant(QSize(70, 23)));

        gridLayout->addWidget(cin_Thickness, 4, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 3, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 9, 1, 1, 1);

        tabWidget->addTab(Tab_ParamSetting, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        cin_Kp = new QLineEdit(tab_2);
        cin_Kp->setObjectName(QStringLiteral("cin_Kp"));
        cin_Kp->setGeometry(QRect(140, 30, 120, 40));
        sizePolicy5.setHeightForWidth(cin_Kp->sizePolicy().hasHeightForWidth());
        cin_Kp->setSizePolicy(sizePolicy5);
        cin_Kp->setMinimumSize(QSize(120, 40));
        cin_Kp->setMaximumSize(QSize(120, 40));
        cin_Kp->setStyleSheet(QString::fromUtf8("/* \346\241\206 */\n"
"border-color: rgb(100, 100, 100);\n"
"border-width: 2px;\n"
"border-style: solid;\n"
"border-radius: 4px;\n"
"/* \350\203\214\346\231\257 */\n"
"background-color: rgb(255, 255, 255);\n"
"/* \345\255\227 */\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;\n"
"color: black;"));
        cin_Kp->setAlignment(Qt::AlignCenter);
        cin_Kp->setProperty("fixedSize", QVariant(QSize(70, 23)));
        cin_Ti = new QLineEdit(tab_2);
        cin_Ti->setObjectName(QStringLiteral("cin_Ti"));
        cin_Ti->setGeometry(QRect(140, 80, 120, 40));
        sizePolicy5.setHeightForWidth(cin_Ti->sizePolicy().hasHeightForWidth());
        cin_Ti->setSizePolicy(sizePolicy5);
        cin_Ti->setMinimumSize(QSize(120, 40));
        cin_Ti->setMaximumSize(QSize(120, 40));
        cin_Ti->setStyleSheet(QString::fromUtf8("/* \346\241\206 */\n"
"border-color: rgb(100, 100, 100);\n"
"border-width: 2px;\n"
"border-style: solid;\n"
"border-radius: 4px;\n"
"/* \350\203\214\346\231\257 */\n"
"background-color: rgb(255, 255, 255);\n"
"/* \345\255\227 */\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;\n"
"color: black;"));
        cin_Ti->setAlignment(Qt::AlignCenter);
        cin_Ti->setProperty("fixedSize", QVariant(QSize(70, 23)));
        Label_Name_Kp = new QLabel(tab_2);
        Label_Name_Kp->setObjectName(QStringLiteral("Label_Name_Kp"));
        Label_Name_Kp->setGeometry(QRect(0, 30, 130, 40));
        Label_Name_Kp->setMinimumSize(QSize(130, 0));
        Label_Name_Kp->setMaximumSize(QSize(130, 16777215));
        Label_Name_Kp->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;"));
        Label_Name_Kp->setLineWidth(0);
        Label_Name_Kp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        Label_Name_Ti = new QLabel(tab_2);
        Label_Name_Ti->setObjectName(QStringLiteral("Label_Name_Ti"));
        Label_Name_Ti->setGeometry(QRect(0, 80, 130, 40));
        Label_Name_Ti->setMinimumSize(QSize(130, 0));
        Label_Name_Ti->setMaximumSize(QSize(130, 16777215));
        Label_Name_Ti->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;"));
        Label_Name_Ti->setLineWidth(0);
        Label_Name_Ti->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        Label_Current = new QLabel(tab_2);
        Label_Current->setObjectName(QStringLiteral("Label_Current"));
        Label_Current->setEnabled(true);
        Label_Current->setGeometry(QRect(420, 40, 150, 50));
        sizePolicy.setHeightForWidth(Label_Current->sizePolicy().hasHeightForWidth());
        Label_Current->setSizePolicy(sizePolicy);
        Label_Current->setMinimumSize(QSize(150, 50));
        Label_Current->setStyleSheet(QLatin1String("font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;\n"
"color: black;\n"
"border: none;"));
        Label_Name_Current = new QLabel(tab_2);
        Label_Name_Current->setObjectName(QStringLiteral("Label_Name_Current"));
        Label_Name_Current->setGeometry(QRect(260, 40, 130, 40));
        Label_Name_Current->setMinimumSize(QSize(130, 0));
        Label_Name_Current->setMaximumSize(QSize(130, 16777215));
        Label_Name_Current->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;"));
        Label_Name_Current->setLineWidth(0);
        Label_Name_Current->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(90, 210, 93, 28));
        pushButton_2 = new QPushButton(tab_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(90, 260, 93, 28));
        Label_RE_Current = new QLabel(tab_2);
        Label_RE_Current->setObjectName(QStringLiteral("Label_RE_Current"));
        Label_RE_Current->setEnabled(true);
        Label_RE_Current->setGeometry(QRect(420, 100, 150, 50));
        sizePolicy.setHeightForWidth(Label_RE_Current->sizePolicy().hasHeightForWidth());
        Label_RE_Current->setSizePolicy(sizePolicy);
        Label_RE_Current->setMinimumSize(QSize(150, 50));
        Label_RE_Current->setStyleSheet(QLatin1String("font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;\n"
"color: black;\n"
"border: none;"));
        Label_Name_Current_2 = new QLabel(tab_2);
        Label_Name_Current_2->setObjectName(QStringLiteral("Label_Name_Current_2"));
        Label_Name_Current_2->setGeometry(QRect(580, 110, 130, 40));
        Label_Name_Current_2->setMinimumSize(QSize(130, 0));
        Label_Name_Current_2->setMaximumSize(QSize(130, 16777215));
        Label_Name_Current_2->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;"));
        Label_Name_Current_2->setLineWidth(0);
        Label_Name_Current_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        Button_CurrPos = new QToolButton(tab_2);
        Button_CurrPos->setObjectName(QStringLiteral("Button_CurrPos"));
        Button_CurrPos->setGeometry(QRect(480, 330, 230, 50));
        sizePolicy.setHeightForWidth(Button_CurrPos->sizePolicy().hasHeightForWidth());
        Button_CurrPos->setSizePolicy(sizePolicy);
        Button_CurrPos->setMinimumSize(QSize(230, 50));
        Button_CurrPos->setMaximumSize(QSize(230, 50));
        Button_CurrPos->setLayoutDirection(Qt::LeftToRight);
        Button_CurrPos->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    /* --- \345\216\237\346\234\211\346\240\267\345\274\217 --- */\n"
"    border-color: rgb(100, 100, 100);\n"
"    border-width: 2px;\n"
"    border-style: solid;\n"
"    background-color: rgb(225, 225, 225);\n"
"    font-family: \"Consolas\", \"Courier New\";\n"
"    font-size: 14pt;\n"
"    font-weight: bold;\n"
"    color: black;\n"
"\n"
"    /* --- \346\216\250\350\215\220\344\274\230\345\214\226\346\240\267\345\274\217 --- */\n"
"    padding: 5px 15px;       /* \344\270\212\344\270\213 5px\357\274\214\345\267\246\345\217\263 15px \345\206\205\350\276\271\350\267\235\357\274\214\351\230\262\346\255\242\346\226\207\345\255\227\350\264\264\350\276\271 */\n"
"    border-radius: 4px;      /* 4 \345\203\217\347\264\240\345\234\206\350\247\222\357\274\214\350\256\251\346\214\211\351\222\256\344\270\215\351\202\243\344\271\210\347\224\237\347\241\254 */\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\347\247\273\344\270\212\345\216\273\347\232\204\346\225\210\346\236\234 */\n"
"QToolButton:hover {\n"
""
                        "    background-color: rgb(240, 240, 240); /* \350\203\214\346\231\257\345\217\230\344\272\256\357\274\214\346\217\220\347\244\272\345\217\257\344\272\244\344\272\222 */\n"
"    border-color: rgb(80, 80, 80);        /* \350\276\271\346\241\206\347\250\215\345\276\256\345\212\240\346\267\261 */\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\214\211\344\270\213\345\216\273\347\232\204\346\225\210\346\236\234 */\n"
"QToolButton:pressed {\n"
"    background-color: rgb(200, 200, 200); /* \350\203\214\346\231\257\345\217\230\346\232\227\357\274\214\346\250\241\346\213\237\345\207\271\351\231\267 */\n"
"    border-color: rgb(60, 60, 60);        /* \350\276\271\346\241\206\346\233\264\346\267\261 */\n"
"    \n"
"    /* \346\250\241\346\213\237\346\214\211\351\222\256\350\242\253\346\214\211\344\270\213\347\232\204\344\275\215\347\247\273\346\204\237 (\345\217\257\351\200\211) */\n"
"    padding-top: 6px;     \n"
"    padding-left: 16px;   \n"
"}"));
        ToolButton_ControlAlgo = new QToolButton(tab_2);
        ToolButton_ControlAlgo->setObjectName(QStringLiteral("ToolButton_ControlAlgo"));
        ToolButton_ControlAlgo->setGeometry(QRect(460, 400, 300, 50));
        sizePolicy.setHeightForWidth(ToolButton_ControlAlgo->sizePolicy().hasHeightForWidth());
        ToolButton_ControlAlgo->setSizePolicy(sizePolicy);
        ToolButton_ControlAlgo->setMinimumSize(QSize(300, 50));
        ToolButton_ControlAlgo->setMaximumSize(QSize(300, 50));
        ToolButton_ControlAlgo->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    /* --- \345\216\237\346\234\211\346\240\267\345\274\217 --- */\n"
"    border-color: rgb(100, 100, 100);\n"
"    border-width: 2px;\n"
"    border-style: solid;\n"
"    background-color: rgb(225, 225, 225);\n"
"    font-family: \"Consolas\", \"Courier New\";\n"
"    font-size: 14pt;\n"
"    font-weight: bold;\n"
"    color: black;\n"
"\n"
"    /* --- \346\216\250\350\215\220\344\274\230\345\214\226\346\240\267\345\274\217 --- */\n"
"    padding: 5px 15px;       /* \344\270\212\344\270\213 5px\357\274\214\345\267\246\345\217\263 15px \345\206\205\350\276\271\350\267\235\357\274\214\351\230\262\346\255\242\346\226\207\345\255\227\350\264\264\350\276\271 */\n"
"    border-radius: 4px;      /* 4 \345\203\217\347\264\240\345\234\206\350\247\222\357\274\214\350\256\251\346\214\211\351\222\256\344\270\215\351\202\243\344\271\210\347\224\237\347\241\254 */\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\347\247\273\344\270\212\345\216\273\347\232\204\346\225\210\346\236\234 */\n"
"QToolButton:hover {\n"
""
                        "    background-color: rgb(240, 240, 240); /* \350\203\214\346\231\257\345\217\230\344\272\256\357\274\214\346\217\220\347\244\272\345\217\257\344\272\244\344\272\222 */\n"
"    border-color: rgb(80, 80, 80);        /* \350\276\271\346\241\206\347\250\215\345\276\256\345\212\240\346\267\261 */\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\214\211\344\270\213\345\216\273\347\232\204\346\225\210\346\236\234 */\n"
"QToolButton:pressed {\n"
"    background-color: rgb(200, 200, 200); /* \350\203\214\346\231\257\345\217\230\346\232\227\357\274\214\346\250\241\346\213\237\345\207\271\351\231\267 */\n"
"    border-color: rgb(60, 60, 60);        /* \350\276\271\346\241\206\346\233\264\346\267\261 */\n"
"    \n"
"    /* \346\250\241\346\213\237\346\214\211\351\222\256\350\242\253\346\214\211\344\270\213\347\232\204\344\275\215\347\247\273\346\204\237 (\345\217\257\351\200\211) */\n"
"    padding-top: 6px;     \n"
"    padding-left: 16px;   \n"
"}"));
        pushButton_3 = new QPushButton(tab_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(310, 330, 93, 28));
        Button_SelCOM = new QToolButton(tab_2);
        Button_SelCOM->setObjectName(QStringLiteral("Button_SelCOM"));
        Button_SelCOM->setGeometry(QRect(470, 250, 200, 50));
        sizePolicy.setHeightForWidth(Button_SelCOM->sizePolicy().hasHeightForWidth());
        Button_SelCOM->setSizePolicy(sizePolicy);
        Button_SelCOM->setMinimumSize(QSize(200, 50));
        Button_SelCOM->setMaximumSize(QSize(200, 50));
        Button_SelCOM->setLayoutDirection(Qt::LeftToRight);
        Button_SelCOM->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    /* --- \345\216\237\346\234\211\346\240\267\345\274\217 --- */\n"
"    border-color: rgb(100, 100, 100);\n"
"    border-width: 2px;\n"
"    border-style: solid;\n"
"    background-color: rgb(225, 225, 225);\n"
"    font-family: \"Consolas\", \"Courier New\";\n"
"    font-size: 14pt;\n"
"    font-weight: bold;\n"
"    color: black;\n"
"\n"
"    /* --- \346\216\250\350\215\220\344\274\230\345\214\226\346\240\267\345\274\217 --- */\n"
"    padding: 5px 15px;       /* \344\270\212\344\270\213 5px\357\274\214\345\267\246\345\217\263 15px \345\206\205\350\276\271\350\267\235\357\274\214\351\230\262\346\255\242\346\226\207\345\255\227\350\264\264\350\276\271 */\n"
"    border-radius: 4px;      /* 4 \345\203\217\347\264\240\345\234\206\350\247\222\357\274\214\350\256\251\346\214\211\351\222\256\344\270\215\351\202\243\344\271\210\347\224\237\347\241\254 */\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\347\247\273\344\270\212\345\216\273\347\232\204\346\225\210\346\236\234 */\n"
"QToolButton:hover {\n"
""
                        "    background-color: rgb(240, 240, 240); /* \350\203\214\346\231\257\345\217\230\344\272\256\357\274\214\346\217\220\347\244\272\345\217\257\344\272\244\344\272\222 */\n"
"    border-color: rgb(80, 80, 80);        /* \350\276\271\346\241\206\347\250\215\345\276\256\345\212\240\346\267\261 */\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\214\211\344\270\213\345\216\273\347\232\204\346\225\210\346\236\234 */\n"
"QToolButton:pressed {\n"
"    background-color: rgb(200, 200, 200); /* \350\203\214\346\231\257\345\217\230\346\232\227\357\274\214\346\250\241\346\213\237\345\207\271\351\231\267 */\n"
"    border-color: rgb(60, 60, 60);        /* \350\276\271\346\241\206\346\233\264\346\267\261 */\n"
"    \n"
"    /* \346\250\241\346\213\237\346\214\211\351\222\256\350\242\253\346\214\211\344\270\213\347\232\204\344\275\215\347\247\273\346\204\237 (\345\217\257\351\200\211) */\n"
"    padding-top: 6px;     \n"
"    padding-left: 16px;   \n"
"}"));
        logText_1 = new QTextEdit(tab_2);
        logText_1->setObjectName(QStringLiteral("logText_1"));
        logText_1->setGeometry(QRect(50, 300, 231, 261));
        sizePolicy.setHeightForWidth(logText_1->sizePolicy().hasHeightForWidth());
        logText_1->setSizePolicy(sizePolicy);
        logText_1->setMinimumSize(QSize(0, 100));
        logText_1->setMaximumSize(QSize(10000, 10200));
        logText_1->setSizeIncrement(QSize(0, 0));
        logText_1->setBaseSize(QSize(0, 0));
        logText_1->setLayoutDirection(Qt::LeftToRight);
        logText_1->setStyleSheet(QLatin1String("font: 10pt \"Consolas\",\"SimHei\";\n"
"background-color: rgb(255, 255, 255);\n"
"border-radius: 12px;\n"
"border: 1px solid rgb(0, 0, 255);\n"
""));
        logText_1->setReadOnly(true);
        Button_logText1_CLR = new QPushButton(tab_2);
        Button_logText1_CLR->setObjectName(QStringLiteral("Button_logText1_CLR"));
        Button_logText1_CLR->setGeometry(QRect(320, 440, 90, 80));
        sizePolicy.setHeightForWidth(Button_logText1_CLR->sizePolicy().hasHeightForWidth());
        Button_logText1_CLR->setSizePolicy(sizePolicy);
        Button_logText1_CLR->setMinimumSize(QSize(0, 0));
        Button_logText1_CLR->setMaximumSize(QSize(90, 16777215));
        Button_logText1_CLR->setStyleSheet(QLatin1String("border: 2px solid rgb(85, 170, 255);\n"
"font: 12pt \"Consolas\",\"SimHei\";\n"
"background-color: rgb(194, 224, 255);"));
        Button_logText1_CLR->setProperty("fixedSize", QVariant(QSize(100, 50)));
        cin_Td = new QLineEdit(tab_2);
        cin_Td->setObjectName(QStringLiteral("cin_Td"));
        cin_Td->setGeometry(QRect(140, 140, 120, 40));
        sizePolicy5.setHeightForWidth(cin_Td->sizePolicy().hasHeightForWidth());
        cin_Td->setSizePolicy(sizePolicy5);
        cin_Td->setMinimumSize(QSize(120, 40));
        cin_Td->setMaximumSize(QSize(120, 40));
        cin_Td->setStyleSheet(QString::fromUtf8("/* \346\241\206 */\n"
"border-color: rgb(100, 100, 100);\n"
"border-width: 2px;\n"
"border-style: solid;\n"
"border-radius: 4px;\n"
"/* \350\203\214\346\231\257 */\n"
"background-color: rgb(255, 255, 255);\n"
"/* \345\255\227 */\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;\n"
"color: black;"));
        cin_Td->setAlignment(Qt::AlignCenter);
        cin_Td->setProperty("fixedSize", QVariant(QSize(70, 23)));
        Label_Name_Td = new QLabel(tab_2);
        Label_Name_Td->setObjectName(QStringLiteral("Label_Name_Td"));
        Label_Name_Td->setGeometry(QRect(0, 130, 130, 40));
        Label_Name_Td->setMinimumSize(QSize(130, 0));
        Label_Name_Td->setMaximumSize(QSize(130, 16777215));
        Label_Name_Td->setStyleSheet(QLatin1String("border: none;\n"
"background-color: none;\n"
"font-family: \"Consolas\", \"Courier New\";\n"
"font-size: 14pt;\n"
"font-weight: bold;"));
        Label_Name_Td->setLineWidth(0);
        Label_Name_Td->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tabWidget->addTab(tab_2, QString());
        tab_54545 = new QWidget();
        tab_54545->setObjectName(QStringLiteral("tab_54545"));
        TableWidget_f = new QTableWidget(tab_54545);
        if (TableWidget_f->columnCount() < 8)
            TableWidget_f->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        TableWidget_f->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        TableWidget_f->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        TableWidget_f->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        TableWidget_f->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        TableWidget_f->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        TableWidget_f->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        TableWidget_f->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        TableWidget_f->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        TableWidget_f->setObjectName(QStringLiteral("TableWidget_f"));
        TableWidget_f->setGeometry(QRect(0, 0, 800, 600));
        tabWidget->addTab(tab_54545, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        TableWidget_r = new QTableWidget(tab_6);
        TableWidget_r->setObjectName(QStringLiteral("TableWidget_r"));
        TableWidget_r->setGeometry(QRect(0, 0, 800, 600));
        tabWidget->addTab(tab_6, QString());

        retranslateUi(Widget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "\345\233\233\346\216\242\351\222\210\346\265\213\347\224\265\351\230\273\347\216\207\347\263\273\347\273\237", Q_NULLPTR));
        Button_SendVoltageRange->setText(QApplication::translate("Widget", "\345\217\221\351\200\201\347\224\265\345\216\213\346\241\243\344\275\215", Q_NULLPTR));
        Button_SendControlVoltage->setText(QApplication::translate("Widget", "\345\217\221\351\200\201\345\216\213\346\216\247", Q_NULLPTR));
        Button_ControlVoltage->setText(QApplication::translate("Widget", "\344\277\235\345\255\230\350\257\245\346\241\243\344\275\215\345\216\213\346\216\247", Q_NULLPTR));
        Button_MeasStart->setText(QApplication::translate("Widget", "\346\265\213 \351\207\217", Q_NULLPTR));
        Button_SendCurrentPosition->setText(QApplication::translate("Widget", "\345\217\221\351\200\201\347\224\265\346\265\201\346\241\243\344\275\215", Q_NULLPTR));
        Button_VolRange->setText(QApplication::translate("Widget", "\347\224\265\345\216\213\346\241\243\344\275\215", Q_NULLPTR));
        ToolButton_MeasureMode->setText(QApplication::translate("Widget", "\346\211\213\345\212\250\345\215\225\347\202\27110\346\254\241\346\265\213\351\207\217", Q_NULLPTR));
        Label_name2_3->setText(QApplication::translate("Widget", "\346\265\213\351\207\217\346\250\241\345\274\217\357\274\232", Q_NULLPTR));
        Label_name1->setText(QApplication::translate("Widget", "\347\224\265\346\265\201\346\241\243\344\275\215\357\274\232", Q_NULLPTR));
        Label_name2->setText(QApplication::translate("Widget", "\347\224\265\345\216\213\346\241\243\344\275\215\357\274\232", Q_NULLPTR));
        Label_name5->setText(QApplication::translate("Widget", "\345\210\235\345\247\213\345\214\226\350\277\233\345\272\246\357\274\232", Q_NULLPTR));
        Label_name4->setText(QApplication::translate("Widget", "COM\345\217\243\357\274\232", Q_NULLPTR));
        Label_NameDataVoltage->setText(QApplication::translate("Widget", "\347\224\265\345\216\213\345\200\274\357\274\232", Q_NULLPTR));
        Label_ResData->setText(QApplication::translate("Widget", "-", Q_NULLPTR));
        Label_NameDataCurrent->setText(QApplication::translate("Widget", "\347\224\265\346\265\201\345\200\274\357\274\232", Q_NULLPTR));
        Label_CurrData->setText(QApplication::translate("Widget", "-", Q_NULLPTR));
        Label_VoltData->setText(QApplication::translate("Widget", "-", Q_NULLPTR));
        Label_name5_2->setText(QApplication::translate("Widget", "\346\265\213\351\207\217\350\277\233\345\272\246\357\274\232", Q_NULLPTR));
        Label_NameDataResistivity->setText(QApplication::translate("Widget", "\347\224\265\351\230\273\347\216\207\357\274\232", Q_NULLPTR));
        Label_MeasureProgress->setText(QApplication::translate("Widget", "\345\256\236\351\252\214\344\274\232\346\210\220\345\212\237\347\232\204", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Widget", "\345\256\236\351\252\214", Q_NULLPTR));
        Label_Name_Temperature->setText(QApplication::translate("Widget", "\346\270\251\345\272\246:", Q_NULLPTR));
        cin_Temperature->setText(QString());
        Label_Name_SampleDiameter_3->setText(QApplication::translate("Widget", "mm", Q_NULLPTR));
        Label_Name_SampleDiameter_4->setText(QApplication::translate("Widget", "mm", Q_NULLPTR));
        Label_Name_SampleDiameter_2->setText(QApplication::translate("Widget", "mm", Q_NULLPTR));
        cin_ProbeSpacing->setText(QString());
        Button_SelSemiType->setText(QApplication::translate("Widget", "P", Q_NULLPTR));
        Label_Name_SampleThickness->setText(QApplication::translate("Widget", "\346\240\267\345\223\201\345\216\232\345\272\246:", Q_NULLPTR));
        Label_Name_SampleThickness_2->setText(QApplication::translate("Widget", "\346\216\242\351\222\210\351\227\264\350\267\235:", Q_NULLPTR));
        Label_Name_SemiType->setText(QApplication::translate("Widget", "\346\240\267\345\223\201\347\261\273\345\236\213:", Q_NULLPTR));
        cin_SampleDiameter->setText(QString());
        Label_Name_SampleDiameter->setText(QApplication::translate("Widget", "\346\240\267\345\223\201\347\233\264\345\276\204:", Q_NULLPTR));
        Label_Name_FspCorrectionFactor->setText(QApplication::translate("Widget", "Fsp:", Q_NULLPTR));
        cin_FspCorrectionFactor->setText(QString());
        Label_Name_SampleDiameter_5->setText(QApplication::translate("Widget", "\342\204\203", Q_NULLPTR));
        cin_CurrErrorBound->setText(QString());
        Label_Name_Temperature_4->setText(QApplication::translate("Widget", "\347\224\265\346\265\201\350\257\257\345\267\256\351\231\220:", Q_NULLPTR));
        Label_Name_SampleDiameter_6->setText(QApplication::translate("Widget", "%", Q_NULLPTR));
        cin_a->setText(QString());
        Label_Name_Temperature_3->setText(QApplication::translate("Widget", "b:", Q_NULLPTR));
        Label_Name_Temperature_2->setText(QApplication::translate("Widget", "a:", Q_NULLPTR));
        cin_b->setText(QString());
        cin_Thickness->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(Tab_ParamSetting), QApplication::translate("Widget", "\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        cin_Kp->setText(QString());
        cin_Ti->setText(QString());
        Label_Name_Kp->setText(QApplication::translate("Widget", "Kp:", Q_NULLPTR));
        Label_Name_Ti->setText(QApplication::translate("Widget", "Ti:", Q_NULLPTR));
        Label_Current->setText(QApplication::translate("Widget", "-", Q_NULLPTR));
        Label_Name_Current->setText(QApplication::translate("Widget", "\347\224\265\346\265\201:", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Widget", "\345\274\200\345\247\213\346\265\213\347\224\265\346\265\201", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Widget", "\345\201\234\346\255\242\346\265\213\347\224\265\346\265\201", Q_NULLPTR));
        Label_RE_Current->setText(QApplication::translate("Widget", "-", Q_NULLPTR));
        Label_Name_Current_2->setText(QApplication::translate("Widget", "%", Q_NULLPTR));
        Button_CurrPos->setText(QApplication::translate("Widget", "\347\224\265\346\265\201\346\241\243\344\275\215", Q_NULLPTR));
        ToolButton_ControlAlgo->setText(QApplication::translate("Widget", "\346\227\240\347\224\265\346\265\201\351\227\255\347\216\257\350\260\203\350\212\202", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("Widget", "\345\274\200\345\247\213\346\265\213\347\224\265\346\265\201", Q_NULLPTR));
        Button_SelCOM->setText(QApplication::translate("Widget", "COM", Q_NULLPTR));
        Button_logText1_CLR->setText(QApplication::translate("Widget", "\346\270\205\351\231\244\n"
"\346\227\245\345\277\227", Q_NULLPTR));
        cin_Td->setText(QString());
        Label_Name_Td->setText(QApplication::translate("Widget", "Td:", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Widget", "\347\224\265\346\265\201\347\233\221\346\265\213", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = TableWidget_f->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Widget", "\346\226\260\345\273\272\345\210\227", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = TableWidget_f->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Widget", "\346\226\260\345\273\272\345\210\227", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = TableWidget_f->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("Widget", "\346\226\260\345\273\272\345\210\227", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = TableWidget_f->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("Widget", "\346\226\260\345\273\272\345\210\227", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = TableWidget_f->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("Widget", "\346\226\260\345\273\272\345\210\227", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = TableWidget_f->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("Widget", "\346\226\260\345\273\272\345\210\227", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = TableWidget_f->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("Widget", "\346\226\260\345\273\272\345\210\227", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = TableWidget_f->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("Widget", "\346\226\260\345\273\272\345\210\227", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_54545), QApplication::translate("Widget", "\351\241\265", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("Widget", "\351\241\265", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
