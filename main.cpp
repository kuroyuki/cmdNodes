#include <QCoreApplication>
#include "dojoapp.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    dojoApp app;
    app.configDojo();

    return a.exec();
}
