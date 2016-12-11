#include "PathVisualizer.h"
#include "VoronoiGenerator.h"
#include "mainwindow.h"
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

    // Run the path finding algorithm, which generates a visualization.
    RenderArea* pathFinderResults = RunPathFinder();

    mainLayout->addWidget(pathFinderResults);
    ui->centralWidget->setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
   delete ui;
}

RenderArea* MainWindow::RunPathFinder()
{
   int canvasWidth = 1000;
   int canvasHeight = 500;

   // Generate the polygonal obstacles.
   VoronoiGenerator vGen(canvasWidth, canvasHeight);
   vector<PolygonFeature> features = vGen.GeneratePolygonFeatures();

   // Generate the Voronoi diagram.
   vector<Point> sourceVertices;
   vector<Segment> sourceEdges;
   unique_ptr<RefinedVoronoiDiagram> vDiagram = vGen.GenerateVoronoiDiagram(features, sourceVertices, sourceEdges);

   // Find the minimal cost path.
   vector<Point> path = vDiagram->graph->FindMinimalCostPath();

   PathVisualizer visualizer(canvasWidth, canvasHeight);
   RenderArea* visualization = visualizer.CreateCanvas(features, vDiagram, sourceVertices, sourceEdges, path);
   visualization->paintToFile();

   return visualization;
}
