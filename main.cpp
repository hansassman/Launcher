#include "src/mainwindow.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Launcher");
    a.setApplicationVersion("1.0");
    const QString config = argc <= 1 ? "config.json" : argv[1];
    MainWindow w(config);
    w.show();
    return a.exec();
}
