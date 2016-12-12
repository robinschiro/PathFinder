#include "PathVisualizer.h"
#include "VoronoiGenerator.h"
#include "RenderAreaWidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QtWidgets>

MainWindow::MainWindow(bool useAltGeneration, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Path Finder");

    QGridLayout *mainLayout = new QGridLayout;

    // Run the path finding algorithm, which generates a visualization.
    RenderArea* pathFinderResults = RunPathFinder(useAltGeneration);

    // Create widget.
    auto pathWidget = new RenderAreaWidget(pathFinderResults);

    mainLayout->addWidget(pathWidget);
    ui->centralWidget->setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
   delete ui;
}

RenderArea* MainWindow::RunPathFinder(bool useAltGeneration)
{
   int canvasWidth = 1000;
   int canvasHeight = 500;

   // Generate the polygonal obstacles.
   VoronoiGenerator vGen(canvasWidth, canvasHeight);
   vector<PolygonFeature> features;
   if (!useAltGeneration)
   {
      features = vGen.GeneratePolygonFeatures();
   }
   else
   {
      features = vGen.GeneratePolygonFeatures2();
   }

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
