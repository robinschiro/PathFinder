#include "SearchableGraph.h"

#include <algorithm>
#include "voronoi_visual_utils.hpp"

SearchableGraph::SearchableGraph(unique_ptr<VoronoiDiagram>& vd, vector<Point>& sourcePoints,
                                 vector<Segment>& sourceSegments, double canvasWidth) :
   sourcePoints(sourcePoints),
   sourceSegments(sourceSegments),
   canvasWidth(canvasWidth)
{
   // Create list of vertices in order to be able to run djikstras.
   for (auto it = vd->edges().begin(); it != vd->edges().end(); ++it)
   {
      std::vector<Point> edgePoints;
      if (!it->is_finite())
      {
         continue;
      }
      else
      {
         Point startPoint(it->vertex0()->x(), it->vertex0()->y());
         edgePoints.push_back(startPoint);
         Point endPoint(it->vertex1()->x(), it->vertex1()->y());
         edgePoints.push_back(endPoint);

         // Create or retrieve the corresponding vertices of the searchable graph.
         shared_ptr<Vertex> startVertex = FindVertex(startPoint);
         shared_ptr<Vertex> endVertex = FindVertex(endPoint);

         double edgeWeight;

         if (it->is_curved())
         {
            GenerateCurvedEdgePoints(*it, &edgePoints, edgeWeight);
         }
         else
         {
            // Calculate edge weight as Euclidean distance from start to end by default.
            edgeWeight = sqrt(pow(endPoint.x() - startPoint.x(), 2) + pow(endPoint.y() - startPoint.y(), 2));
         }

         // Create an edge, update the start vertex.
         Edge newEdge(startVertex, endVertex, edgePoints, edgeWeight);
         startVertex->neighbors.push_back(newEdge);
      }
   }

   std::cout << "Created List" << std::endl;
}

shared_ptr<Vertex> SearchableGraph::FindVertex(Point& point)
{
   for (shared_ptr<Vertex> vertex : vertices)
   {
      if (vertex->hasPoint(point))
      {
         return vertex;
      }
   }

   // If the vertex does not exist, create it.
   auto newVertex = make_shared<Vertex>(nextVertexId++, point);
   vertices.push_back(newVertex);
   return newVertex;
}

void SearchableGraph::RemoveVertex(int id)
{
   for ( auto vertIter = vertices.begin(); vertIter != vertices.end(); vertIter++)
   {
      if (id == (*vertIter)->id)
      {
         vertices.erase(vertIter);
         return;
      }
   }
}

Point SearchableGraph::RetrievePoint(const VCell& cell)
{
   SourceIndex index = cell.source_index();
   SourceCat category = cell.source_category();
   if (category == SOURCE_CATEGORY_SINGLE_POINT) {
      return sourcePoints[index];
   }
   index -= sourcePoints.size();
   if (category == SOURCE_CATEGORY_SEGMENT_START_POINT) {
      return low(sourceSegments[index]);
   }
   else
   {
      return high(sourceSegments[index]);
   }
}

Segment SearchableGraph::RetrieveSegment(const VCell& cell)
{
   SourceIndex index = cell.source_index() - sourcePoints.size();
   return sourceSegments[index];
}

// Based on source:
// http://www.boost.org/doc/libs/1_54_0/libs/polygon/example/voronoi_visualizer.cpp
void SearchableGraph::GenerateCurvedEdgePoints(const VEdge& edge, std::vector<Point>* sampled_edge,
                                               double& edgeWeight)
{
   double max_dist = 1E-4 * canvasWidth;

   Point point = edge.cell()->contains_point() ?
                 RetrievePoint(*edge.cell()) :
                 RetrievePoint(*edge.twin()->cell());

   Segment segment = edge.cell()->contains_point() ?
                     RetrieveSegment(*edge.twin()->cell()) :
                     RetrieveSegment(*edge.cell());

   voronoi_visual_utils<CoordNumType>::discretize(point, segment, max_dist, sampled_edge, edgeWeight);
}

vector<shared_ptr<Vertex>> SearchableGraph::RunDjikstras(Vertex source)
{
   double inf = 1E9;
   vector<shared_ptr<Vertex>> prev(vertices.size());
   vector<double> dist(vertices.size());

   for (int i = 0; i < dist.size(); i++)
   {
      dist[i] = inf;
   }
   dist[source.id] = 0;

   while (!vertices.empty())
   {
      // Find the vertex with the smallest distance to the source.
      shared_ptr<Vertex> next;
      int minDist = inf;
      for (auto vertex : vertices)
      {
          if ( dist[vertex->id] <= minDist )
          {
              next = vertex;
              minDist = dist[vertex->id];
          }
      }
//      vertices.erase(std::find(vertices.begin(), vertices.end(), next));
      RemoveVertex(next->id);

      for (Edge neighbor : next->neighbors)
      {
         int neighborId = neighbor.dest->id;
         double potentialDist = minDist + neighbor.weight;
         if (potentialDist < dist[neighborId])
         {
            dist[neighborId] = potentialDist;
            prev[neighborId] = next;
         }
      }
   }

   return prev;
}
