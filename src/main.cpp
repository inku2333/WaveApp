#include "MainWindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[]) {
    // Qt 6 已默认开启 AA_EnableHighDpiScaling
    QApplication app(argc, argv);

    QFile file(":/styles/main.qss");
    if (file.open(QFile::ReadOnly)) {
        app.setStyleSheet(file.readAll());
        file.close();
    }

    MainWindow w;
    w.show();
    return app.exec();
}
