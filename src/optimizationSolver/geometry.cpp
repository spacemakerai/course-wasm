
#include "geometry.h"
#include<cmath>


float lengthOfLine(Point point1, Point point2)
{
    float distance = sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
    return distance;
}
float getArea(Building rectangularBuilding)
{
    Polygon polygon = rectangularBuilding.ground_polygon;
    float length = lengthOfLine(polygon[0], polygon[1]);
    float width = lengthOfLine(polygon[1], polygon[2]);
    return length * width;
}

float getVolume(Building building)
{
    float polygonArea = getArea(building);
    float volume = polygonArea * building.height;
    return volume;
}