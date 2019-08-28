#include <vector>

#include "geometry.h"
#include "optimize.h"

int NUMBER_OF_COORDINATES_PER_BUILDING = 4;
Objective mainObjective = Objective::DISTANCE_TO_BUS_STOP;

Buildings convertParametersToBuildings(const float *positions, int numberOfBuildings);
void convertBuildingsToParameters(Buildings buildings, float *positions);

extern "C" void move(float *positions, int n)
{
    Buildings inputBuildings = convertParametersToBuildings(positions, n);
    Buildings optimizedBuildings = optimizeBuildings(inputBuildings, mainObjective);
    convertBuildingsToParameters(optimizedBuildings, positions);
}

Buildings convertParametersToBuildings(const float *positions, int n)
{
    Buildings inputBuildings;
    for (int i = 0; i < n; i++)
    {
        int length = positions[i];

        i++;

        Polygon ground_polygon;

        for (int j = 0; j < length; j += 2, i += 2)
        {
            Point point{positions[i], positions[i + 1]};
            ground_polygon.push_back(point);
        }
        Building building = {positions[i], ground_polygon};
        inputBuildings.push_back(building);
    }
    return inputBuildings;
}

void convertBuildingsToParameters(Buildings buildings, float *positions)
{
    int index = 0;
    for (int i = 0; i < buildings.size(); i++)
    {
        Building building = buildings[i];
        positions[index++] = building.groundPolygon.size() * 2;
        for (int j = 0; j < building.groundPolygon.size(); j++)
        {
            Point point = building.groundPolygon[j];
            positions[index++] = point.x;
            positions[index++] = point.y;
        }
        positions[index++] = building.height;
    }
}

int main(int argc, char *argv[])
{
    float positions[18] = {0, 0, 10, 0, 10, 5, 0, 5, 10, 20, 0, 40, 0, 40, 10, 20, 10, 10};
    move(positions, 18);
}
