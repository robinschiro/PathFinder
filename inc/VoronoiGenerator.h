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
   unique_ptr<RefinedVoronoiDiagram> GenerateVoronoiDiagram(vector<PolygonFeature>& features,
                                                            vector<Point>& points,
                                                            vector<Segment>& segments);

private:
   int maxX;
   int maxY;
   vector<Segment> borders;

};

#endif // VORONOIGENERATOR_H
