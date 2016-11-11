#ifndef PATHVISUALIZER_H
#define PATHVISUALIZER_H

#include "inc/renderarea.h"
#include "boost/polygon/voronoi.hpp"
#include "inc/VoronoiGenerator.h"
using namespace boost::polygon;

class PathVisualizer
{
public:
   PathVisualizer();
   
   RenderArea* CreateCanvas();
   
   void DrawPolygonFeatures(QPainterPath& canvas, vector<PolygonFeature> features);
   
   void DrawVoronoiEdges(QPainterPath& canvas, voronoi_diagram<double> diagram);
   
   void DrawTypeOneEdges(QPainterPath& canvas, vector<Segment> diagram);
   void DrawTypeTwoEdges(QPainterPath& canvas, vector<Segment> diagram);
   void DrawTypeTjreeEdges(QPainterPath& canvas, vector<Segment> diagram);
};

#endif // PATHVISUALIZER_H
