#ifndef PATHVISUALIZER_H
#define PATHVISUALIZER_H

#include "inc/renderarea.h"
#include "boost/polygon/voronoi.hpp"
#include "inc/VoronoiGenerator.h"
using namespace boost::polygon;

class PathVisualizer
{
public:
   PathVisualizer(int canvasWidth, int canvasHeight);
   
   RenderArea* CreateCanvas(vector<PolygonFeature>& features, VoronoiDiagram* vDiagram, vector<Point>& vertices, 
                            vector<Segment>& edges);
   
private:
   int canvasWidth;
   int canvasHeight;
   vector<Point> sourceVertices;
   vector<Segment> sourceEdges;
   
   
   void DrawPolygonFeatures(QPainterPath& canvas, vector<PolygonFeature>& features);
   
   void DrawVoronoiEdges(QPainterPath& canvas, VoronoiDiagram* diagram);
   void GenerateCurvedEdgePoints(const Edge& edge, std::vector<Point>* sampled_edge);
   Point RetrievePoint(const Cell& cell);
   Segment RetrieveSegment(const Cell& cell);
   
   void DrawTypeOneEdges(QPainterPath& canvas, vector<Segment>& diagram);
   void DrawTypeTwoEdges(QPainterPath& canvas, vector<Segment>& diagram);
   void DrawTypeThreeEdges(QPainterPath& canvas, vector<Segment>& diagram);
};

#endif // PATHVISUALIZER_H
