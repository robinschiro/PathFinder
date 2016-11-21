#ifndef SEARCHABLEGRAPH_H
#define SEARCHABLEGRAPH_H

#include "GeometryStructures.h"
#include "Util.h"

class SearchableGraph
{
public:

   SearchableGraph(unique_ptr<VoronoiDiagram>& diagram, vector<Point>& sourcePoints,
                   vector<Segment>& sourceSegments, double canvasWidth);

   // Generate the minimal cost path from the graph of a refined Voronoi diagram.
   vector<Segment> ProducePath();

   vector<shared_ptr<Vertex>> vertices;

private:

   // Maintain a list of all the vertices in the graph.
   vector<Point> sourcePoints;
   vector<Segment> sourceSegments;
   double canvasWidth;
   int nextVertexId = 0;

   // Retrieve an index of vertex from the list of vertices based on point value.
   // Creates a vertex if it doesn't already exist.
   shared_ptr<Vertex> FindVertex(Point& point);

   void RemoveVertex(int id);

   // Run Djistra's algorithm on a graph given the adjacency list and source point.
   // A list of links to previous vertices is returned in order to reconstruct the
   // optimal path.
   vector<shared_ptr<Vertex>> RunDjikstras(Vertex source);

   void GenerateCurvedEdgePoints(const VEdge& edge, vector<Point>* sampled_edge, double& edgeWeight);
   Point RetrievePoint(const VCell& cell);
   Segment RetrieveSegment(const VCell& cell);

};

#endif // SEARCHABLEGRAPH_H
