#include "VoronoiGenerator.h"

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

vector<PolygonFeature> VoronoiGenerator::GeneratePolygonFeatures2()
{
   vector<PolygonFeature> features;
   PolygonFeature feature;

   feature.add(Point(50, 30));
   feature.add(Point(50, 100));
   feature.add(Point(10, 100));
   feature.add(Point(10, 30));
   features.push_back(feature);
   feature.vertices.clear();

   feature.add(Point(500, 300));
   feature.add(Point(500, 350));
   feature.add(Point(400, 350));
   feature.add(Point(400, 300));
   features.push_back(feature);
   feature.vertices.clear();

   feature.add(Point(200, 150));
   feature.add(Point(200, 250));
   feature.add(Point(275, 250));
   feature.add(Point(275, 150));
   features.push_back(feature);
   feature.vertices.clear();


   feature.add(Point(750, 410));
   feature.add(Point(750, 485));
   feature.add(Point(625, 485));
   feature.add(Point(675, 410));
   features.push_back(feature);
   feature.vertices.clear();

   feature.add(Point(50, 405));
   feature.add(Point(50, 470));
   feature.add(Point(150, 470));
   feature.add(Point(100, 415));
   features.push_back(feature);
   feature.vertices.clear();

   feature.add(Point(450, 60));
   feature.add(Point(450, 120));
   feature.add(Point(550, 100));
   feature.add(Point(550, 75));
   features.push_back(feature);
   feature.vertices.clear();

   feature.add(Point(800, 20));
   feature.add(Point(800, 75));
   feature.add(Point(880, 100));
   feature.add(Point(860, 30));
   features.push_back(feature);
   feature.vertices.clear();

   feature.add(Point(600, 275));
   feature.add(Point(600, 320));
   feature.add(Point(680, 330));
   feature.add(Point(650, 240));
   features.push_back(feature);
   feature.vertices.clear();

   feature.add(Point(850, 350));
   feature.add(Point(850, 420));
   feature.add(Point(920, 435));
   feature.add(Point(920, 370));
   features.push_back(feature);
   feature.vertices.clear();

   feature.add(Point(280, 380));
   feature.add(Point(400, 470));
   feature.add(Point(250, 465));
   feature.add(Point(200, 360));
   features.push_back(feature);
   feature.vertices.clear();



//   feature.add(Point(400, 200));
//   feature.add(Point(400, 300));
//   feature.add(Point(350, 200));
//   feature.add(Point(350, 300));
//   features.push_back(feature);
//   feature.vertices.clear();

//   feature.add(Point(1, 2));
//   feature.add(Point(1, 3));
//   feature.add(Point(4, 2));
//   feature.add(Point(4, 3));
//   features.push_back(feature);
//   feature.vertices.clear();

//   feature.add(Point(1, 2));
//   feature.add(Point(1, 3));
//   feature.add(Point(4, 2));
//   feature.add(Point(4, 3));
//   features.push_back(feature);
//   feature.vertices.clear();

//   feature.add(Point(1, 2));
//   feature.add(Point(1, 3));
//   feature.add(Point(4, 2));
//   feature.add(Point(4, 3));
//   features.push_back(feature);
//   feature.vertices.clear();

//   feature.add(Point(1, 2));
//   feature.add(Point(1, 3));
//   feature.add(Point(4, 2));
//   feature.add(Point(4, 3));
//   features.push_back(feature);
//   feature.vertices.clear();

//   feature.add(Point(1, 2));
//   feature.add(Point(1, 3));
//   feature.add(Point(4, 2));
//   feature.add(Point(4, 3));
//   features.push_back(feature);
//   feature.vertices.clear();

//   feature.add(Point(1, 2));
//   feature.add(Point(1, 3));
//   feature.add(Point(4, 2));
//   feature.add(Point(4, 3));
//   features.push_back(feature);
//   feature.vertices.clear();

//   feature.add(Point(1, 2));
//   feature.add(Point(1, 3));
//   feature.add(Point(4, 2));
//   feature.add(Point(4, 3));
//   features.push_back(feature);
//   feature.vertices.clear();

//   feature.add(Point(1, 2));
//   feature.add(Point(1, 3));
//   feature.add(Point(4, 2));
//   feature.add(Point(4, 3));
//   features.push_back(feature);
//   feature.vertices.clear();



   return features;
}

unique_ptr<RefinedVoronoiDiagram> VoronoiGenerator::GenerateVoronoiDiagram(vector<PolygonFeature>& features,
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
   unique_ptr<RefinedVoronoiDiagram> refinedDiagram = make_unique<RefinedVoronoiDiagram>(diagram, points, segments,
                                                                                         borders, maxX);
   return refinedDiagram;
}
