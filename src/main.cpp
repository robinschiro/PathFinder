#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    bool showWindow = true;
    if (argc >= 2)
    {
       string noWindowString(argv[1]);
       showWindow = (noWindowString != "-noWindow");
       MainWindow::RunPathFinder();
    }

    if (showWindow)
    {
       QApplication a(argc, argv);
       MainWindow w;
       w.show();
       return a.exec();
    }
}
