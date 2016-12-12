#include "mainwindow.h"
#include <QApplication>

#define SHOW_WINDOW_ARG "-showWindow"
#define USE_TEN_OBSTACLES_ARG "-useTenObstacles"

int main(int argc, char *argv[])
{
   string firstArgString;
   string secondArgString;
   if (argc >= 2)
   {
      firstArgString.assign(argv[1]);
   }
   if (argc >= 3)
   {
      secondArgString.assign(argv[2]);
   }

   bool showWindow = (firstArgString == SHOW_WINDOW_ARG) || (secondArgString == SHOW_WINDOW_ARG);
   bool useTenObstacles = (firstArgString == USE_TEN_OBSTACLES_ARG) || (secondArgString == USE_TEN_OBSTACLES_ARG);

   if (showWindow)
   {
      QApplication a(argc, argv);
      MainWindow w(useTenObstacles);
      w.show();
      return a.exec();
   }
   else
   {
      // Just run the path finder and produce an output image.
      MainWindow::RunPathFinder(useTenObstacles);
      return 0;
   }
}
