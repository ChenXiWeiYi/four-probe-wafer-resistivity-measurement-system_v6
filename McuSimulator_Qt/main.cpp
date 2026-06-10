#include "simulatorwindow.h"
#include <QApplication>

/**
 * @brief main
 * @author 刘嘉诚
 * @date 2026.06.10
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SimulatorWindow window;
    window.show();

    return app.exec();
}
