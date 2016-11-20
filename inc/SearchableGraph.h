#ifndef SEARCHABLEGRAPH_H
#define SEARCHABLEGRAPH_H

#include <RefinedVoronoiDiagram.h>
#include <set>
#include <queue>

struct Vertex;
struct Edge;

struct Vertex
{
   Point point;
   std::set<Edge> neighbors;
   bool visited = false;

   Vertex(Point point) : point(point) {}
};

struct Edge
{
    Vertex dest;
    double weight;

    Edge(Vertex& dest, double weight) : dest(dest), weight(weight) {}
};

class SearchableGraph
{
public:

   SearchableGraph();

   // Generate the minimal cost path from the graph of a refined Voronoi diagram.
   vector<Segment> ProducePath();

private:

   // Maintain a list of all the vertices in the graph.
   std::set<Vertex> vertices;

};

#endif // SEARCHABLEGRAPH_H
