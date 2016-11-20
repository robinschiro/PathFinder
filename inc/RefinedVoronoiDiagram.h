#ifndef REFINEDVORONOIDIAGRAM_H
#define REFINEDVORONOIDIAGRAM_H

#include <memory>
#include <vector>

#include "boost/polygon/voronoi.hpp"
#include "boost/polygon/polygon.hpp"

using namespace boost::polygon;
using namespace std;

typedef double CoordNumType;
typedef point_data<CoordNumType> Point;
typedef segment_data<CoordNumType> Segment;
typedef voronoi_diagram<CoordNumType> VoronoiDiagram;
typedef VoronoiDiagram::vertex_type VVertex;
typedef VoronoiDiagram::edge_type VEdge;
typedef VoronoiDiagram::cell_type VCell;
typedef VoronoiDiagram::cell_type::source_index_type SourceIndex;
typedef VoronoiDiagram::cell_type::source_category_type SourceCat;

using namespace std;


template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

struct PolygonFeature
{
   vector<Point> vertices;

   void add(Point p)
   {
      vertices.push_back(p);
   }
};

struct Vector
{
   double x;
   double y;

   Vector(double x, double y) : x(x), y(y){}

   double dot(const Vector& other)
   {
      return (this->x * other.x) + (this->y * other.y);
   }

   double magSquared()
   {
      return (this->x * this->x) + (this->y * this->y);
   }

};

class RefinedVoronoiDiagram
{
public:
   RefinedVoronoiDiagram();

   unique_ptr<VoronoiDiagram> voronoiDiagram;
   vector<Segment> typeOneSegments;
   vector<Segment> typeTwoSegments;
   vector<Segment> borders;

};

#endif // REFINEDVORONOIDIAGRAM_H
