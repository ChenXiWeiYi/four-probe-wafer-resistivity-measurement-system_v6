#include <QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);  // 创建应用程序对象

    Widget window;  // 创建主窗口对象
    window.show();  // 显示窗口

    return app.exec();  // 进入应用程序的主事件循环
}
