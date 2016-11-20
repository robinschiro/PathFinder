#ifndef VORONOIGENERATOR_H
#define VORONOIGENERATOR_H

#include <vector>
#include "boost/polygon/voronoi.hpp"
#include "boost/polygon/polygon.hpp"

#include "RefinedVoronoiDiagram.h"

using namespace boost::polygon;
using namespace std;

class VoronoiGenerator
{
public:

   VoronoiGenerator(int maxX, int maxY);

   // For now, generate a set of fixed polygon features.
   // TODO: Generate random polygon features.
   vector<PolygonFeature> GeneratePolygonFeatures();

   // Given a set of polygonal features, construct a Voronoi diagram.
   // Update the passed-in empty vectors of source vertices and edges.
   RefinedVoronoiDiagram* GenerateVoronoiDiagram(vector<PolygonFeature>& features,
                                                 vector<Point>& points,
                                                 vector<Segment>& segments);

private:
   int maxX;
   int maxY;
   vector<Segment> borders;

   // Computer the typeOneSegments that must be made to the base Voronoi diagram.
   unique_ptr<RefinedVoronoiDiagram> GenerateRefinements(unique_ptr<VoronoiDiagram>& diagram,
                                                         vector<Point>& points,
                                                         vector<Segment>& segments);

   // Given an input site point and a cell, create type one segments for all Voronoi vertices in a cell.
   void CreateTypeOneSegments(VCell& cell, vector<Segment>& typeOneSegments,
                              Point& inputSiteStart, Point* inputSiteEnd = NULL);

   // Given an input site point and a cell, create type two segments for all Voronoi edges in a cell.
   void CreateTypeTwoSegments(VCell& cell, vector<Segment>& typeTwoSegments, Point& inputSiteStart);
};

#endif // VORONOIGENERATOR_H
