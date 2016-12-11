#include "PathVisualizer.h"
#include "voronoi_visual_utils.hpp"

void generateRandomPoints(QPainterPath& canvas, int numPoints, int thickness,
                          int maxXValue, int maxYValue,
                          int minXValue = 0, int minYValue = 0)
{
    for (int i = 0; i < numPoints; i++)
    {
        int randX = (rand() % (maxXValue - minXValue)) + minXValue;
        int randY = (rand() % (maxYValue - minYValue)) + minYValue;
        canvas.addEllipse(randX, randY, thickness, thickness);
    }
}

// Guarantee that bounding boxes of generated polygons do not overlap.
void generateRandomPolygons(QPainterPath& canvas, int numPolygons,
                            int maxNumSides, int maxGridWidth, int maxGridHeight)
{
//    // Polygons must have at least three sides.
//    if (maxNumSides < 3)
//    {
//        return;
//    }

//    for (int i = 0; i < numPolygons; i++)
//    {
//        int numSides = (rand() % (maxNumSides - 3)) + 3;

//        int randX = (rand() % (maxGridWidth - minGridWidth)) + minGridWidth;
//        int randY = (rand() % (maxGridHeight - minGridHeight)) + minGridHeight;
//        canvas.addEllipse(randX, randY, thickness, thickness);
//        canvas.ad
//    }

//   QPainterPath rectPath;
//   rectPath.moveTo(20.0, 30.0);
//   rectPath.lineTo(80.0, 30.0);
//   rectPath.lineTo(80.0, 70.0);
//   rectPath.lineTo(20.0, 70.0);
//   rectPath.closeSubpath();
}

PathVisualizer::PathVisualizer(int canvasWidth, int canvasHeight) :
   canvasWidth(canvasWidth),
   canvasHeight(canvasHeight)
{
}

RenderArea* PathVisualizer::CreateCanvas(vector<PolygonFeature>& features, unique_ptr<RefinedVoronoiDiagram>& rvDiagram,
                                         vector<Point>& vertices, vector<Segment>& edges, vector<Point>& minimalPath)
{
   int startEndBuffer = 100;

   sourceVertices = vertices;
   sourceEdges = edges;

   vector<RenderLayer> layers;


//   generateRandomPoints(grid, 1, 4, startEndBuffer, canvasHeight);
//   generateRandomPoints(grid, 1, 4, canvasWidth, canvasHeight, canvasWidth - startEndBuffer);

   // Draw borders.
   layers.push_back(this->DrawSegments(rvDiagram->borders));

   // Draw the type one segments.
   layers.push_back(this->DrawSegments(rvDiagram->typeOneSegments, Qt::cyan));

   // Draw Voronoi edges.
   layers.push_back(this->DrawVoronoiEdges(rvDiagram));

   // Draw features.
   layers.push_back(this->DrawPolygonFeatures(features));

   // Draw path
   layers.push_back(this->DrawPathThroughPoints(minimalPath, Qt::green, Qt::SolidLine, 2));

   // Generate start and end points.
   layers.push_back(this->DrawStartAndEndPoints());

   return new RenderArea(layers, canvasWidth, canvasHeight);
}

RenderLayer PathVisualizer::DrawStartAndEndPoints()
{
   RenderLayer layer;
   layer.fillColor1 = Qt::darkGreen;
   layer.fillColor2 = Qt::darkGreen;

   int thickness = 5;

   QPainterPath endpoints;

   QPointF bottomLeft(0, canvasHeight);
   QPointF topRight(canvasWidth, 0);
   endpoints.addEllipse(bottomLeft, thickness, thickness);
   endpoints.addEllipse(topRight, thickness, thickness);
   layer.path = endpoints;

   return layer;
}

RenderLayer PathVisualizer::DrawPolygonFeatures(vector<PolygonFeature>& features)
{
   RenderLayer layer;

   // Make the polygons red.
   layer.penColor = Qt::red;
   layer.fillColor1 = Qt::red;
   layer.fillColor2 = Qt::red;

   for (PolygonFeature feature : features)
   {
      QPolygonF poly;
      for (Point p : feature.vertices)
      {
         poly << QPointF(p.x(), p.y());
      }
      poly << poly[0];

      layer.path.addPolygon(poly);
   }

   return layer;
}

// Iterate through all of the edges of the voronoi diagram and draw them.
RenderLayer PathVisualizer::DrawVoronoiEdges(unique_ptr<RefinedVoronoiDiagram>& vd)
{
   RenderLayer layer;

   for (auto vertex : vd->graph->vertices)
   {
      for (auto edge : vertex->neighbors)
      {
         vector<Point>& points = edge.discretization;
         RenderLayer edgeLayer = DrawPathThroughPoints(points);
         layer.ConcatenateLayerPath(edgeLayer);
      }
   }

   return layer;
}

RenderLayer PathVisualizer::DrawPathThroughPoints(vector<Point>& points, QColor color, Qt::PenStyle penStyle,
                                                  int penWidth)
{
   RenderLayer layer;
   layer.penColor = color;
   layer.penStyle = penStyle;
   layer.fillColor1 = Qt::transparent;
   layer.fillColor2 = Qt::transparent;
   layer.penWidth = penWidth;

   if (points.size() >= 2)
   {
      // Draw the edge.
      QPainterPath edge;
      edge.moveTo(points[0].x(), points[0].y());
      for (int i = 1; i < points.size(); i++)
      {
         edge.lineTo(points[i].x(), points[i].y());
      }

      layer.path.addPath(edge);
   }

   return layer;
}

RenderLayer PathVisualizer::DrawSegments(vector<Segment>& segments, QColor color, Qt::PenStyle penStyle)
{
   RenderLayer layer;
   layer.penColor = color;
   layer.penStyle = penStyle;

   for (Segment segment : segments)
   {
      QPainterPath edge;
      edge.moveTo(segment.low().x(), segment.low().y());
      edge.lineTo(segment.high().x(), segment.high().y());

      layer.path.addPath(edge);
   }

   return layer;
}


