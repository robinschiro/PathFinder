#ifndef PATHVISUALIZER_H
#define PATHVISUALIZER_H

#include <memory>

#include "inc/RenderArea.h"
#include "boost/polygon/voronoi.hpp"
#include "inc/VoronoiGenerator.h"

using namespace boost::polygon;
using namespace std;

class PathVisualizer
{
public:
   PathVisualizer(int canvasWidth, int canvasHeight);

   RenderArea* CreateCanvas(vector<PolygonFeature>& features, RefinedVoronoiDiagram* vDiagram, vector<Point>& vertices,
                                    vector<Segment>& edges);

private:
   int canvasWidth;
   int canvasHeight;
   vector<Point> sourceVertices;
   vector<Segment> sourceEdges;


   RenderLayer DrawPolygonFeatures(vector<PolygonFeature>& features);

   RenderLayer DrawVoronoiEdges(unique_ptr<VoronoiDiagram> diagram);
   void GenerateCurvedEdgePoints(const Edge& edge, std::vector<Point>* sampled_edge);
   Point RetrievePoint(const Cell& cell);
   Segment RetrieveSegment(const Cell& cell);

   RenderLayer DrawSegments(vector<Segment>& segments, QColor color = Qt::black, Qt::PenStyle penStyle = Qt::SolidLine);
   void DrawTypeTwoEdges(QPainterPath& canvas, vector<Segment>& diagram);
   void DrawTypeThreeEdges(QPainterPath& canvas, vector<Segment>& diagram);
};

#endif // PATHVISUALIZER_H
