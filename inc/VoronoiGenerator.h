#ifndef VORONOIGENERATOR_H
#define VORONOIGENERATOR_H

#include <vector>
#include "boost/polygon/voronoi.hpp"
#include "boost/polygon/polygon.hpp"
using namespace boost::polygon;
using namespace std;

typedef point_data<int> Point;
typedef segment_data<int> Segment;

struct PolygonFeature
{
   vector<Point> vertices;
};

class VoronoiGenerator
{
public:  
   
   VoronoiGenerator();
      
   voronoi_diagram<double>* GenerateVoronoiDiagram(vector<PolygonFeature>& features);
   
private:
   
};

#endif // VORONOIGENERATOR_H
