
#include "geometry.h"
#include<cmath>


float lengthOfLine(Point point1, Point point2){
    float distance = sqrt(pow(point1.x - point2.x, 2) + pow(point1.y-point2.y,2));
    return distance;
}
float simpleArea(Building building){
    Polygon rectangularPolygon = building.ground_polygon;
    float length = lengthOfLine(rectangularPolygon[0], rectangularPolygon[1]);
    float width = lengthOfLine(rectangularPolygon[1], rectangularPolygon[2]);
    return length * width;
}
