#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    bool showWindow = true;
    if (argc >= 2)
    {
       string noWindowString(argv[1]);
       showWindow = (noWindowString != "-noWindow");
    }

    if (showWindow)
    {
      w.show();
    }

    return a.exec();
}
