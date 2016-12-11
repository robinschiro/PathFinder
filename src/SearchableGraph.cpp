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
         shared_ptr<Vertex> startVertex = FindOrCreateVertex(startPoint);
         shared_ptr<Vertex> endVertex = FindOrCreateVertex(endPoint);

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
         Edge newEdge(startVertex, endVertex, edgePoints, edgeWeight, it->is_primary());
         startVertex->neighbors.push_back(newEdge);
      }
   }
}

vector<Point> SearchableGraph::FindMinimalCostPath()
{
   vector<Point> path;

   // Find the source and target points.
   // It will be the bottom-left most point in the graph.
   shared_ptr<Vertex> source = vertices[0];
   shared_ptr<Vertex> target = vertices[0];
   for (auto vertex : vertices)
   {
      if ((vertex->point.x() <= source->point.x()) &&
          (vertex->point.y() >= source->point.y()))
      {
         source = vertex;
      }

      if ((vertex->point.x() >= target->point.x()) &&
          (vertex->point.y() <= target->point.y()))
      {
         target = vertex;
      }
   }

   // Run Djikstra's algorithm.
   vector<shared_ptr<Vertex>> previousVertices = RunDjikstras(source);

   shared_ptr<Vertex> temp = target;
   while (NULL != temp)
   {
      int destId = temp->id;
      temp = previousVertices[temp->id];

      // Insert points for edge.
      if (NULL != temp)
      {
         for (Edge edge : temp->neighbors)
         {
            if (destId == edge.dest->id)
            {
               path.insert(path.begin(), edge.discretization.begin(), edge.discretization.end());
            }
         }
      }
   }

   return path;
}

shared_ptr<Vertex> SearchableGraph::FindOrCreateVertex(Point& point)
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

bool SearchableGraph::VertexVectorContains(int id, vector<shared_ptr<Vertex>>& verts)
{
   for (auto vertex : verts)
   {
      if (id == vertex->id)
      {
         return true;
      }
   }

   return false;
}

void SearchableGraph::RemoveVertex(int id, vector<shared_ptr<Vertex>>& verts)
{
   for ( auto vertIter = verts.begin(); vertIter != verts.end(); vertIter++)
   {
      if (id == (*vertIter)->id)
      {
         verts.erase(vertIter);
         return;
      }
   }
}

// Implementation based on source:
// http://www.boost.org/doc/libs/1_54_0/libs/polygon/example/voronoi_visualizer.cpp
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

// Implementation based on source:
// http://www.boost.org/doc/libs/1_54_0/libs/polygon/example/voronoi_visualizer.cpp
Segment SearchableGraph::RetrieveSegment(const VCell& cell)
{
   SourceIndex index = cell.source_index() - sourcePoints.size();
   return sourceSegments[index];
}

// Implementation based on source:
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

vector<shared_ptr<Vertex>> SearchableGraph::RunDjikstras(shared_ptr<Vertex> source)
{
   double inf = 1E9;

   // Make a copy of vertices vector.
   vector<shared_ptr<Vertex>> verticesCopy(vertices.begin(), vertices.end());

   // Keep track of the path of previous vertices.
   // This is needed to reconstruct the optimal path.
   vector<shared_ptr<Vertex>> prev(verticesCopy.size());
   vector<double> dist(verticesCopy.size());

   for (int i = 0; i < dist.size(); i++)
   {
      dist[i] = inf;
   }
   dist[source->id] = 0;

   while (!verticesCopy.empty())
   {
      // Find the vertex with the smallest distance to the source.
      shared_ptr<Vertex> next;
      int minDist = inf;
      for (auto vertex : verticesCopy)
      {
          if ( dist[vertex->id] <= minDist )
          {
              next = vertex;
              minDist = dist[vertex->id];
          }
      }
//      verticesCopy.erase(std::find(verticesCopy.begin(), verticesCopy.end(), next));
      RemoveVertex(next->id, verticesCopy);

      for (Edge neighbor : next->neighbors)
      {
         int neighborId = neighbor.dest->id;
         // Skip edges that have destination vertices that have already been examined
         // or that are secondary edges.
         if (!VertexVectorContains(neighborId, verticesCopy) || !neighbor.isPrimary)
         {
            continue;
         }
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
