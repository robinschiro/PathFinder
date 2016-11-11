#include "inc/PathVisualizer.h"

PathVisualizer::PathVisualizer()
{
   
}

void generateRandomPoints(QPainterPath& canvas, int numPoints, int thickness, 
                          int maxXValue, int maxYValue, 
                          int minXValue = 0, int minYValue = 0)
{
    for (int i = 0; i < numPoints; i++)
    {
        int randX = (rand() % (maxXValue - minXValue)) + minXValue;
        int randY = (rand() % (maxYValue - minYValue)) + minYValue;
        canvas.addEllipse(randX, randY, thickness, thickness);
    }
}

void generateFixedPolygons(QPainterPath& canvas)
{
   // Generate triangle.
   QPolygonF triangle;
   triangle << QPointF(150, 30) << QPointF(160, 180) << QPointF(350, 50);
   
   // Generate pentagon.
   QPolygonF pentagon;
   pentagon << QPointF(400, 250); 
   
   canvas.addPolygon(triangle);
}

// Guarantee that bounding boxes of generated polygons do not overlap.
void generateRandomPolygons(QPainterPath& canvas, int numPolygons,
                            int maxNumSides, int maxGridWidth, int maxGridHeight)
{
//    // Polygons must have at least three sides.
//    if (maxNumSides < 3)
//    {
//        return;
//    }

//    for (int i = 0; i < numPolygons; i++)
//    {
//        int numSides = (rand() % (maxNumSides - 3)) + 3;

//        int randX = (rand() % (maxGridWidth - minGridWidth)) + minGridWidth;
//        int randY = (rand() % (maxGridHeight - minGridHeight)) + minGridHeight;
//        canvas.addEllipse(randX, randY, thickness, thickness);
//        canvas.ad
//    }
   
//   QPainterPath rectPath;
//   rectPath.moveTo(20.0, 30.0);
//   rectPath.lineTo(80.0, 30.0);
//   rectPath.lineTo(80.0, 70.0);
//   rectPath.lineTo(20.0, 70.0);
//   rectPath.closeSubpath();
}

RenderArea* PathVisualizer::CreateCanvas()
{
   // Generate start and end points.
   QPainterPath grid;
   generateRandomPoints(grid, 1, 4, 100, 500);
   generateRandomPoints(grid, 1, 4, 1000, 500, 900);
   
   // Generate set of polygons used for testing.
   generateFixedPolygons(grid);

   return new RenderArea(grid, 1000, 500);
}

void PathVisualizer::DrawPolygonFeatures(QPainterPath& canvas, vector<PolygonFeature> features)
{
   
}

void PathVisualizer::DrawVoronoiEdges(QPainterPath& canvas, voronoi_diagram<double> diagram)
{
   
}
