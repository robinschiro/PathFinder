#include "inc/PathVisualizer.h"
#include "inc/voronoi_visual_utils.hpp"

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

RenderArea* PathVisualizer::CreateCanvas(vector<PolygonFeature>& features, RefinedVoronoiDiagram* rvDiagram,
                                         vector<Point>& vertices, vector<Segment>& edges)
{
   int startEndBuffer = 100;

   sourceVertices = vertices;
   sourceEdges = edges;

   vector<RenderLayer> layers;
//   // Generate start and end points.
//   generateRandomPoints(grid, 1, 4, startEndBuffer, canvasHeight);
//   generateRandomPoints(grid, 1, 4, canvasWidth, canvasHeight, canvasWidth - startEndBuffer);

   // Draw borders.
   layers.push_back(this->DrawSegments(rvDiagram->borders));

   // Draw the type one segments.
   layers.push_back(this->DrawSegments(rvDiagram->typeOneSegments, Qt::green));

   // Draw Voronoi edges.
   layers.push_back(this->DrawVoronoiEdges(std::move(rvDiagram->voronoiDiagram)));

   // Draw features.
   layers.push_back(this->DrawPolygonFeatures(features));


   return new RenderArea(layers, canvasWidth, canvasHeight);
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

      layer.path.addPolygon(poly);
   }

   return layer;
}

Point PathVisualizer::RetrievePoint(const Cell& cell)
{
   SourceIndex index = cell.source_index();
   SourceCat category = cell.source_category();
   if (category == SOURCE_CATEGORY_SINGLE_POINT) {
      return sourceVertices[index];
   }
   index -= sourceVertices.size();
   if (category == SOURCE_CATEGORY_SEGMENT_START_POINT) {
      return low(sourceEdges[index]);
   }
   else
   {
      return high(sourceEdges[index]);
   }
}

Segment PathVisualizer::RetrieveSegment(const Cell& cell)
{
   SourceIndex index = cell.source_index() - sourceVertices.size();
   return sourceEdges[index];
}

// Based on source:
// http://www.boost.org/doc/libs/1_54_0/libs/polygon/example/voronoi_visualizer.cpp
void PathVisualizer::GenerateCurvedEdgePoints(const Edge& edge, std::vector<Point>* sampled_edge)
{
   double max_dist = 1E-3 * canvasWidth;

   Point point = edge.cell()->contains_point() ?
                 RetrievePoint(*edge.cell()) :
                 RetrievePoint(*edge.twin()->cell());

   Segment segment = edge.cell()->contains_point() ?
                     RetrieveSegment(*edge.twin()->cell()) :
                     RetrieveSegment(*edge.cell());

   voronoi_visual_utils<CoordNumType>::discretize(point, segment, max_dist, sampled_edge);
}

// Based on source:
// http://www.boost.org/doc/libs/1_54_0/libs/polygon/example/voronoi_visualizer.cpp
RenderLayer PathVisualizer::DrawVoronoiEdges(unique_ptr<VoronoiDiagram> vd)
{
   RenderLayer layer;

   for (auto it = vd->edges().begin(); it != vd->edges().end(); ++it)
   {
      std::vector<Point> samples;
      if (!it->is_finite())
      {
         continue;
//        clip_infinite_edge(*it, &samples);
      }
      else
      {
         Point vertex0(it->vertex0()->x(), it->vertex0()->y());
         samples.push_back(vertex0);
         Point vertex1(it->vertex1()->x(), it->vertex1()->y());
         samples.push_back(vertex1);
         if (it->is_curved())
         {
            GenerateCurvedEdgePoints(*it, &samples);
         }
      }

      if (samples.size() >= 2)
      {
         // Draw the edge.
         QPainterPath edge;
         edge.moveTo(samples[0].x(), samples[0].y());
         for (int i = 1; i < samples.size(); i++)
         {
            edge.lineTo(samples[i].x(), samples[i].y());
         }

         layer.path.addPath(edge);
      }
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


