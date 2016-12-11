#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "RenderArea.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    static RenderArea* RunPathFinder();

    ~MainWindow();

protected:
//    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
