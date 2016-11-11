#include "inc/PathVisualizer.h"
#include "inc/mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Path Finder");

    QGridLayout *mainLayout = new QGridLayout;

    PathVisualizer visualizer;
    mainLayout->addWidget(visualizer.CreateCanvas());
    ui->centralWidget->setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
