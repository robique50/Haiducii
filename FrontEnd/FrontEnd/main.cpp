#include "FrontEnd.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FrontEnd w;
    w.show();
    return a.exec();
}
