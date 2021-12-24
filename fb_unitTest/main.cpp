#include <QCoreApplication>
#include "testfunction.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    testFunction1();
    testFunction2();
    testFunction3();

    return a.exec();
}
