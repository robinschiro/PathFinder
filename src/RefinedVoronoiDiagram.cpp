#include "RefinedVoronoiDiagram.h"

#include <exception>

RefinedVoronoiDiagram::RefinedVoronoiDiagram(unique_ptr<VoronoiDiagram>& diagram,
                                             vector<Point>& points,
                                             vector<Segment>& segments,
                                             vector<Segment> borders,
                                             int canvasWidth) :
   voronoiDiagram(std::move(diagram)),
   borders(borders)
{
   GenerateRefinements(voronoiDiagram, points, segments);

   graph = make_unique<SearchableGraph>(voronoiDiagram, points, segments, canvasWidth);
}


void RefinedVoronoiDiagram::GenerateRefinements(unique_ptr<VoronoiDiagram>& diagram,
                                                vector<Point>& points,
                                                vector<Segment>& segments)
{
   // Iterate through all cells of the diagram.
   for (VCell cell : diagram->cells())
   {
      std::size_t index = cell.source_index();

      // If the input site is a point.
      if (cell.contains_point())
      {
         Point inputSitePoint;

         // Proceed if the input site is an independent source point.
         if (index < points.size())
         {
            inputSitePoint = points[index];
            CreateTypeOneSegments(cell, inputSitePoint);
         }
         // The input site is an endpoint of one of the source segments.
         else
         {
            index -= points.size();

            if ((index < segments.size()) && (index >= 0))
            {
               // Determine which endpoint serves as the input site.
               if (cell.source_category() == SOURCE_CATEGORY_SEGMENT_START_POINT)
               {
                  inputSitePoint = segments[index].low();
               }
               else
               {
                  inputSitePoint = segments[index].high();
               }

               CreateTypeOneSegments(cell, inputSitePoint);
            }
            else
            {
               throw std::runtime_error("Invalid index into segments vector when segment endpoint is input site.");
            }
         }

         // Create the type two segments.


      }
      else
      {
         index -= points.size();

         if ((index < segments.size()) && (index >= 0))
         {
            Point start = segments[index].low();
            Point end = segments[index].high();

            CreateTypeOneSegments(cell, start, &end);
         }
         else
         {
            throw std::runtime_error("Invalid index into segments vector when segment is input site.");
         }
      }
   }
}

void RefinedVoronoiDiagram::CreateTypeOneSegments(VCell& cell, Point& inputSiteStart, Point* inputSiteEnd)
{
   // Iterate through all of the Voronoi vertices of the cell.
   VEdge* edge = cell.incident_edge();
   do
   {
      if (edge->is_finite())
      {
         VVertex* voronoiVertex = edge->vertex0();

         // The input site is a point obstacle.
         if (NULL == inputSiteEnd)
         {
            typeOneSegments.push_back(Segment(inputSiteStart, Point(voronoiVertex->x(), voronoiVertex->y())));
         }
         // The input site is a segment obstacle.
         else
         {
            Point end = *inputSiteEnd;

            // Create a segment from the the Voronoi vertex to the closest point on the segment.
            Vector vecToVertex((voronoiVertex->x() - inputSiteStart.x()), (voronoiVertex->y() - inputSiteStart.y()));
            Vector vecToEnd((end.x() - inputSiteStart.x()), (end.y() - inputSiteStart.y()));

            double scalar = vecToVertex.dot(vecToEnd) / vecToEnd.magSquared();
            Point projectedPoint(inputSiteStart.x() + scalar*vecToEnd.x, inputSiteStart.y() + scalar*vecToEnd.y);
            typeOneSegments.push_back(Segment(projectedPoint, Point(voronoiVertex->x(), voronoiVertex->y())));
         }
      }
      edge = edge->next();
   }
   while (edge != cell.incident_edge());
}

void RefinedVoronoiDiagram::CreateTypeTwoSegments(VCell& cell, Point& inputSitePoint)
{
   // Iterate through all of the Voronoi edges of the cell.
   VEdge* edge = cell.incident_edge();
   do
   {
      if (edge->is_finite())
      {

      }
      edge = edge->next();
   }
   while (edge != cell.incident_edge());
}
