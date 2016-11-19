#include "inc/VoronoiGenerator.h"

#include <exception>

VoronoiGenerator::VoronoiGenerator(int maxX, int maxY) : maxX(maxX), maxY(maxY)
{
   // Create segments to represent the borders of the diagram.
   borders.push_back(Segment(Point(0, 0), Point(maxX, 0)));
   borders.push_back(Segment(Point(maxX, 0), Point(maxX, maxY)));
   borders.push_back(Segment(Point(maxX, maxY), Point(0, maxY)));
   borders.push_back(Segment(Point(0, maxY), Point(0, 0)));
}

vector<PolygonFeature> VoronoiGenerator::GeneratePolygonFeatures()
{
   vector<PolygonFeature> features;

   // Generate triangle.
   PolygonFeature triangle;
   triangle.add(Point(150, 30));
   triangle.add(Point(160, 180));
   triangle.add(Point(350, 50));
   features.push_back(triangle);

   // Generate pentagon.
   PolygonFeature pentagon;
   pentagon.add(Point(400, 250));
   pentagon.add(Point(450, 350));
   pentagon.add(Point(425, 425));
   pentagon.add(Point(350, 425));
   pentagon.add(Point(275, 350));
   features.push_back(pentagon);

   // Generate hexagon.
   PolygonFeature hexagon;
   hexagon.add(Point(670, 200));
   hexagon.add(Point(750, 275));
   hexagon.add(Point(725, 375));
   hexagon.add(Point(615, 390));
   hexagon.add(Point(575, 300));
   hexagon.add(Point(625, 225));
   features.push_back(hexagon);

   // Generate diamond
   PolygonFeature diamond;
   diamond.add(Point(875, 25));
   diamond.add(Point(950, 125));
   diamond.add(Point(875, 225));
   diamond.add(Point(800, 125));
   features.push_back(diamond);

   return features;
}

RefinedVoronoiDiagram* VoronoiGenerator::GenerateVoronoiDiagram(vector<PolygonFeature>& features,
                                                                vector<Point>& points,
                                                                vector<Segment>& segments)
{
   // Generate list of vertices and edges from features.
   for (auto featureIter = features.begin(); featureIter != features.end(); featureIter++)
   {
      PolygonFeature feature = *featureIter;
      Point lastPoint;
      bool passedFirstPoint = false;
      for (auto vertIter = feature.vertices.begin(); vertIter != feature.vertices.end(); vertIter++)
      {
         // Store each individual vertex.
         points.push_back(*vertIter);

         if (passedFirstPoint)
         {
            segments.push_back(Segment(*vertIter, lastPoint));
         }
         else
         {
            passedFirstPoint = true;
         }

         lastPoint = *vertIter;
      }

      // Push back the last segment.
      segments.push_back(Segment(lastPoint, *feature.vertices.begin()));
   }

   // Add the bounding edges.
   segments.insert(segments.end(), borders.begin(), borders.end());

   // Construct diagram.
   unique_ptr<VoronoiDiagram> diagram = make_unique<VoronoiDiagram>();
   construct_voronoi(points.begin(), points.end(), segments.begin(), segments.end(), diagram.get());

   // Create a version of the diagram that includes refinements.
   unique_ptr<RefinedVoronoiDiagram> refinedDiagram = GenerateRefinements(diagram, points, segments);

   return refinedDiagram.release();
}

unique_ptr<RefinedVoronoiDiagram> VoronoiGenerator::GenerateRefinements(unique_ptr<VoronoiDiagram>& diagram,
                                                                        vector<Point>& points,
                                                                        vector<Segment>& segments)
{
   unique_ptr<RefinedVoronoiDiagram> refinedDiagram = make_unique<RefinedVoronoiDiagram>();
   refinedDiagram->borders = this->borders;
   vector<Segment>& typeOneSegments = refinedDiagram->typeOneSegments;

   // Iterate through all cells of the diagram.
   for (Cell cell : diagram->cells())
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
            CreateTypeOneSegments(cell, typeOneSegments, inputSitePoint);
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

               CreateTypeOneSegments(cell, typeOneSegments, inputSitePoint);
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

            CreateTypeOneSegments(cell, typeOneSegments, start, &end);
         }
         else
         {
            throw std::runtime_error("Invalid index into segments vector when segment is input site.");
         }
      }
   }

   // Encapsulate the base diagram.
   refinedDiagram->voronoiDiagram = std::move(diagram);

   return refinedDiagram;
}

void VoronoiGenerator::CreateTypeOneSegments(Cell& cell, vector<Segment>& typeOneSegments,
                                             Point& inputSiteStart, Point* inputSiteEnd)
{
   // Iterate through all of the Voronoi vertices of the cell.
   Edge* edge = cell.incident_edge();
   do
   {
      if (edge->is_finite())
      {
         Vertex* voronoiVertex = edge->vertex0();

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

void VoronoiGenerator::CreateTypeTwoSegments(Cell& cell, vector<Segment>& typeTwoSegments, Point& inputSitePoint)
{
   // Iterate through all of the Voronoi edges of the cell.
   Edge* edge = cell.incident_edge();
   do
   {
      if (edge->is_finite())
      {

      }
      edge = edge->next();
   }
   while (edge != cell.incident_edge());
}
