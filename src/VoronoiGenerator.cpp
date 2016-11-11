#include "inc/VoronoiGenerator.h"

VoronoiGenerator::VoronoiGenerator(int maxX, int maxY) : maxX(maxX), maxY(maxY)
{   
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
   hexagon.add(Point(675, 350));
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

VoronoiDiagram* VoronoiGenerator::GenerateVoronoiDiagram(vector<PolygonFeature>& features, 
                                                         vector<Point>& vertices,
                                                         vector<Segment>& edges)
{
   // Generate list of vertices and edges from features.  
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
   }
   
   // Add the bounding edges.
   edges.push_back(Segment(Point(0, 0), Point(maxX, 0)));
   edges.push_back(Segment(Point(maxX, 0), Point(maxX, maxY)));
   edges.push_back(Segment(Point(maxX, maxY), Point(0, maxY)));
   edges.push_back(Segment(Point(0, maxY), Point(0, 0)));
   
   // Construct diagram.
   VoronoiDiagram* diagram = new VoronoiDiagram();
   construct_voronoi(vertices.begin(), vertices.end(), edges.begin(), edges.end(), diagram);
   
   return diagram;   
}
