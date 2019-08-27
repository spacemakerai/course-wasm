#include <vector>

#include "geometry.h"
#include "optimize.h"

int PARAMETERS_PER_BUILDING = 9;
int NUMBER_OF_COORDINATES_PER_BUILDING = 4;
Objective mainObjective = Objective::DISTANCE_TO_BUS_STOP;

Buildings convertParametersToBuildings(const float* positions, int numberOfBuildings);
void convertBuildingsToParameters(Buildings buildings, float *positions);

extern "C" void move(float *positions, int n)
{
    int numberOfBuildings = n/PARAMETERS_PER_BUILDING;
    Buildings inputBuildings = convertParametersToBuildings(positions, numberOfBuildings);
    Buildings optimizedBuildings = optimizeBuildings(inputBuildings, mainObjective);
    convertBuildingsToParameters(optimizedBuildings, positions);
}

Buildings convertParametersToBuildings(const float* positions, int numberOfBuildings)
{
    Buildings inputBuildings;
    for (int i= 0; i<numberOfBuildings; i++)
    {
        Polygon ground_polygon;
        for (int j=0; j<NUMBER_OF_COORDINATES_PER_BUILDING; j++)
        {
            Point point{positions[i*PARAMETERS_PER_BUILDING + j*2], positions[i*PARAMETERS_PER_BUILDING + j*2 +1]};
            ground_polygon.push_back(point);
        }
        Building building = {positions[i*PARAMETERS_PER_BUILDING + 8], ground_polygon};
        inputBuildings.push_back(building);
    }
    return inputBuildings;
}

void convertBuildingsToParameters(Buildings buildings, float *positions)
{
    int numberOfBuildings = (int) buildings.size();
    for (int i= 0; i<numberOfBuildings; i++)
    {
        Building building = buildings[i];
        for (int j=0; j<NUMBER_OF_COORDINATES_PER_BUILDING; j++)
        {
            Point point = building.groundPolygon[j];
            positions[i*PARAMETERS_PER_BUILDING + j*2] = point.x;
            positions[i*PARAMETERS_PER_BUILDING + j*2 + 1] = point.y;
            positions[i*PARAMETERS_PER_BUILDING + 8] = building.height;
        }
    }

}

int main(int argc, char *argv[])
{
    float positions[18] = {0, 0, 10, 0, 10, 5, 0, 5, 10, 20, 0, 40, 0, 40, 10, 20, 10, 10};
    move(positions, 18);
}
