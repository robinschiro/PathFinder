#ifndef GEOMETRYSTRUCTURES_H
#define GEOMETRYSTRUCTURES_H

#include "boost/polygon/voronoi.hpp"
#include "boost/polygon/polygon.hpp"
#include <memory>
#include <vector>

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

struct Vertex;
struct Edge;

struct Vertex
{
   int id = -1;
   Point point;
   vector<Edge> neighbors;

   Vertex() {}
   Vertex(int id, Point point) : id(id), point(point) {}

   // Overload equality.
   bool operator==(const Vertex& other)
   {
      return other.id == this->id;
   }

   bool areSame(double a, double b)
   {
      return fabs(a - b) < 1E-9;
   }

   bool hasPoint(const Point& point)
   {
      return areSame(this->point.x(), point.x()) && areSame(this->point.y(), point.y());
   }
};

struct Edge
{
   shared_ptr<Vertex> src;
   shared_ptr<Vertex> dest;
   vector<Point> discretization;
   double weight;
   bool isPrimary = true;

   Edge(shared_ptr<Vertex> src, shared_ptr<Vertex> dest, vector<Point> points, double weight, bool isPrimary) :
      src(src), dest(dest), discretization(points), weight(weight), isPrimary(isPrimary) {}
};


#endif // GEOMETRYSTRUCTURES_H
