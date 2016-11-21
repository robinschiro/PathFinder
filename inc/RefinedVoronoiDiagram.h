#ifndef REFINEDVORONOIDIAGRAM_H
#define REFINEDVORONOIDIAGRAM_H

#include <memory>
#include <vector>

#include "GeometryStructures.h"
#include "Util.h"
#include "SearchableGraph.h"

class RefinedVoronoiDiagram
{
public:
   RefinedVoronoiDiagram(unique_ptr<VoronoiDiagram>& diagram,
                         vector<Point>& points,
                         vector<Segment>& segments,
                         vector<Segment> borders,
                         int canvasWidth);

   unique_ptr<VoronoiDiagram> voronoiDiagram;
   unique_ptr<SearchableGraph> graph;
   vector<Segment> typeOneSegments;
   vector<Segment> typeTwoSegments;
   vector<Segment> borders;

private:
   // Computer the typeOneSegments that must be made to the base Voronoi diagram.
   void GenerateRefinements(unique_ptr<VoronoiDiagram>& diagram,
                            vector<Point>& points,
                            vector<Segment>& segments);

   // Given an input site point and a cell, create type one segments for all Voronoi vertices in a cell.
   void CreateTypeOneSegments(VCell& cell, Point& inputSiteStart, Point* inputSiteEnd = NULL);

   // Given an input site point and a cell, create type two segments for all Voronoi edges in a cell.
   void CreateTypeTwoSegments(VCell& cell, Point& inputSiteStart);

};

#endif // REFINEDVORONOIDIAGRAM_H
