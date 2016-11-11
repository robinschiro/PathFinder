#include "inc/VoronoiGenerator.h"

VoronoiGenerator::VoronoiGenerator()
{
   
}



voronoi_diagram<double>* VoronoiGenerator::GenerateVoronoiDiagram(vector<PolygonFeature>& features)
{
   // Generate list of vertices and edges from features.
   vector<Point> vertices;
   vector<Segment> edges;
   
   for (auto featureIter = features.begin(); featureIter != features.end(); featureIter++)
   {
      PolygonFeature feature = *featureIter;
      Point lastPoint;
      bool passedFirstPoint = false;
      for (auto vertIter = feature.vertices.begin(); vertIter != feature.vertices.end(); vertIter++)
      {
         vertices.push_back(*vertIter);
         
         if (passedFirstPoint)
         {
            edges.push_back(Segment(*vertIter, lastPoint));
         }
         else
         {
            passedFirstPoint = true;
         }
         
         lastPoint = *vertIter;
      }
      
      // Push back the last segment.
      edges.push_back(Segment(lastPoint, *feature.vertices.begin()));
      
      // Construct diagram.
      voronoi_diagram<double>* diagram = new voronoi_diagram<double>();
      construct_voronoi(vertices.begin(), vertices.end(), edges.begin(), edges.end(), diagram);
      
      return diagram;      
   }
   
}
