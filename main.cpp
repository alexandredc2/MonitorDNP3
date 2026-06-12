#include "MonitorDNP3.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MonitorDNP3 window;
    window.show();
    return app.exec();
}
