#include "widget.h"
#include "ui_widget.h"
#include <QAction>
#include <QDebug>
#include <QDataStream>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QVBoxLayout>
#include <QDir>

/**
 * @brief Widget::Popup_Window 弹出普通的不需要操作的窗口
 * @param title 窗口标题
 * @param content 显示内容
 * @date 2025.10.20
 */
void Widget::Popup_Window(QString title, QString content)
{
    // 1. 创建弹出窗口（父窗口可设为nullptr，避免父窗口影响）
    QWidget *popup = new QWidget(nullptr);
    // 2. 关键：强制设置为顶级窗口，确保显示标题栏和关闭按钮
    popup->setWindowFlags(Qt::Window);
    // 4. 窗口关闭时自动释放内存
    popup->setAttribute(Qt::WA_DeleteOnClose);
    // 5. 窗口属性
    popup->setWindowTitle(title); // 标题栏文字
    popup->setFixedSize(250, 100);                    // 窗口大小
    QFont font("SimHei", 12); // "SimHei"是黑体的标准字体名
    //    popup->setFont(font); // 为窗口整体设置字体，子控件可继承
    // 6. 弹出窗口内的内容
    QLabel *label = new QLabel(content, popup);
    label->setAlignment(Qt::AlignCenter);
    QVBoxLayout *layout = new QVBoxLayout(popup);
    layout->addWidget(label);
    // 7. 显示窗口
    popup->show();
}

/**
 * @brief Widget::popupConfirmDialog 弹出包含确认和取消的窗口
 * @param windowTitle 弹出窗口的标题
 * @param content 弹出窗口的内容
 * @return 点击确认还是取消
 * @date 2025.10.21
 */
bool Widget::Popup_Confirm_Dialog(const QString &windowTitle, const QString &content)
{
    bool flag = false; // 通用标志：true=确定，false=取消/关闭
    // 创建弹窗（通用设置）
    QDialog *popup = new QDialog(nullptr);
    popup->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint); // 带关闭按钮
    popup->setAttribute(Qt::WA_DeleteOnClose); // 关闭后自动释放
    popup->setWindowTitle(windowTitle); // 用参数设置窗口标题
    popup->setFixedSize(250, 100); // 保持固定大小（如需通用可也作为参数，这里暂固定）
    // 提示标签：用参数设置内容
    QLabel *label = new QLabel(content, popup);
    label->setAlignment(Qt::AlignCenter);
    // 确认/取消按钮
    QPushButton *okBtn = new QPushButton("确定", popup);
    QPushButton *cancelBtn = new QPushButton("取消", popup);
    // 确定按钮：设置标志为true，关闭弹窗
    connect(okBtn, &QPushButton::clicked, this, [&](){
    flag = true;
    popup->done(QDialog::Accepted);
    });
    // 取消按钮：标志保持false，关闭弹窗
    connect(cancelBtn, &QPushButton::clicked, this, [&](){
    popup->done(QDialog::Rejected);
    });
    // 布局（通用结构不变）
    QVBoxLayout *popupLayout = new QVBoxLayout(popup);
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);
    popupLayout->addWidget(label);
    popupLayout->addLayout(btnLayout);
    popupLayout->addStretch();
    // 模态显示，等待用户操作
    popup->exec();
    return flag; // 返回用户选择结果
}

/**
 * @brief Widget::initLineEdiftPlaceholder 设置输入的占位符
 * @param lineEdit 设置占位符的LineEdit
 * @param placeholderText 占位符
 * @date 2025.10.20
 */
void Widget::initLineEditPlaceholder(QLineEdit *lineEdit, const QString &placeholderText)
{
    lineEdit->setPlaceholderText(placeholderText);
#if 0
    lineEdit->setStyleSheet(R"(
QLineEdit {
font: 12pt "Consolas", "SimHei";       /* 字体：12pt，优先Consolas，其次SimHei */
border: 2px solid rgb(50, 50, 150);   /* 边框：2px实线，深蓝色 */
border-radius: 2px;                   /* 边框圆角：2px */
background-color: rgb(240, 248, 240); /* 背景色：浅青绿色 */
padding: 2px;                         /* 内边距：避免文字贴边框（可选） */
}
)");
#endif
}




/**
 * @brief Widget::AppendTimeToFile 添加时间戳
 * @param FileName
 * @date 2026.01.29
 */
void Widget::AppendTimeToFile(const QString& FileName)
{
    QString Dir_App = QCoreApplication::applicationDirPath();   // 获取可执行文件所在目录
    QString Dir_Output = Dir_App + "/Data/";    // 定义子目录
    QDir dir;
    if (!dir.exists(Dir_Output)){
        dir.mkpath(Dir_Output);
    }
    QString FilePath = Dir_Output + FileName;   // 构建完整路径
    QFile file(FilePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "文件打开失败：" << file.errorString() << "路径：" << FilePath;
        return;
    }
    QDateTime CurrentTime = QDateTime::currentDateTime();
    QString TimeStamp = CurrentTime.toString("yyyy-MM-dd hh:mm:ss"); // 时间戳格式
    QTextStream out(&file);
    out << TimeStamp << "\n";
    file.close();
}


