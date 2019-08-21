
#include "geometry.h"
#include<cmath>
#include <numeric>


float lengthOfLine(Point point1, Point point2)
{
    float distance = sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
    return distance;
}

Point getCentroid(const Polygon& polygon)
{
    std::vector<float> xCoordinates;
    std::vector<float> yCoordinates;

    for (Point cornerPoint: polygon)
    {
        xCoordinates.push_back(cornerPoint.x);
        yCoordinates.push_back(cornerPoint.y);
    }
    float sumOfXCoordinate = std::accumulate(xCoordinates.begin(), xCoordinates.end(), 0.0);
    float sumOfYCoordinate = std::accumulate(yCoordinates.begin(), yCoordinates.end(), 0.0);

    int numberOfCornerPoints = polygon.size();
    float centroidXCoordinate = sumOfXCoordinate / (float) numberOfCornerPoints;
    float centroidYCoordinate = sumOfYCoordinate / (float) numberOfCornerPoints;

    return {centroidXCoordinate, centroidYCoordinate};
}

float getArea(const Building& rectangularBuilding)
{
    Polygon polygon = rectangularBuilding.groundPolygon;
    float length = lengthOfLine(polygon[0], polygon[1]);
    float width = lengthOfLine(polygon[1], polygon[2]);
    return length * width;
}

float getVolume(const Building& building)
{
    float polygonArea = getArea(building);
    float volume = polygonArea * building.height;
    return volume;
}