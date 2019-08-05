//
// Created by Kristine Hagen on 2019-08-05.
//

#include "geometry.h"
#include<cmath>


double lengthOfLine(Point point1, Point point2){
    double distance = sqrt(pow(point1.x - point2.x, 2) + pow(point1.y-point2.y,2));
    return distance;
}
double simpleArea(Building building){
    Polygon rectangularPolygon = building.ground_polygon;
    double length = lengthOfLine(rectangularPolygon[0], rectangularPolygon[1]);
    double width = lengthOfLine(rectangularPolygon[1], rectangularPolygon[2]);
    return length * width;
}
double getHeight(Building building) { return building.end_z - building.start_z; };
