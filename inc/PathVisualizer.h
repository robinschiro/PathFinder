#ifndef PATHVISUALIZER_H
#define PATHVISUALIZER_H

#include <memory>

#include "boost/polygon/voronoi.hpp"

#include "RenderArea.h"
#include "VoronoiGenerator.h"

using namespace boost::polygon;
using namespace std;

class PathVisualizer
{
public:
   PathVisualizer(int canvasWidth, int canvasHeight);

   RenderArea* CreateCanvas(vector<PolygonFeature>& features,
                            unique_ptr<RefinedVoronoiDiagram>& vDiagram,
                            vector<Point>& vertices,
                            vector<Segment>& edges,
                            vector<Point>& minimalPath);

private:
   int canvasWidth;
   int canvasHeight;
   vector<Point> sourceVertices;
   vector<Segment> sourceEdges;


   RenderLayer DrawStartAndEndPoints();

   RenderLayer DrawPolygonFeatures(vector<PolygonFeature>& features);

   RenderLayer DrawVoronoiEdges(unique_ptr<RefinedVoronoiDiagram>& diagram);

   RenderLayer DrawPathThroughPoints(vector<Point>& points, QColor color = Qt::black,
                                     Qt::PenStyle penStyle = Qt::SolidLine, int penWidth = 1);
   RenderLayer DrawSegments(vector<Segment>& segments, QColor color = Qt::black, Qt::PenStyle penStyle = Qt::SolidLine);
   void DrawTypeTwoEdges(QPainterPath& canvas, vector<Segment>& diagram);
   void DrawTypeThreeEdges(QPainterPath& canvas, vector<Segment>& diagram);
};

#endif // PATHVISUALIZER_H
