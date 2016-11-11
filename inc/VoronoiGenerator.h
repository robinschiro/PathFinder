#ifndef VORONOIGENERATOR_H
#define VORONOIGENERATOR_H

#include <vector>
#include "boost/polygon/voronoi.hpp"
#include "boost/polygon/polygon.hpp"
using namespace boost::polygon;
using namespace std;

typedef double CoordNumType;
typedef point_data<CoordNumType> Point;
typedef segment_data<CoordNumType> Segment;
typedef voronoi_diagram<CoordNumType> VoronoiDiagram;
typedef VoronoiDiagram::edge_type Edge;
typedef VoronoiDiagram::cell_type Cell;
typedef VoronoiDiagram::cell_type::source_index_type SourceIndex;
typedef VoronoiDiagram::cell_type::source_category_type SourceCat;

struct PolygonFeature
{
   vector<Point> vertices;
   
   void add(Point p)
   {
      vertices.push_back(p);
   }
};

class VoronoiGenerator
{
public:  
   
   VoronoiGenerator(int maxX, int maxY);
      
   // For now, generate a set of fixed polygon features.
   // TODO: Generate random polygon features.
   vector<PolygonFeature> GeneratePolygonFeatures();
   
   VoronoiDiagram* GenerateVoronoiDiagram(vector<PolygonFeature>& features, 
                                          vector<Point>& vertices,
                                          vector<Segment>& edges);
   
private:
   int maxX;
   int maxY;   
};

#endif // VORONOIGENERATOR_H
