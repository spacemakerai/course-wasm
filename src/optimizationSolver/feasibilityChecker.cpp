
#include <numeric>
#include "feasibilityChecker.h"

float getAverageHeight(Buildings buildings)
{
    std::vector<float> buildingVolumes;
    buildingVolumes.resize(buildings.size());
    std::transform(buildings.begin(), buildings.end(), buildingVolumes.begin(), getVolume);
    float totalVolume = std::accumulate(buildingVolumes.begin(), buildingVolumes.end(), 0.0);

    std::vector<float> buildingAreas;
    buildingAreas.resize(buildings.size());
    std::transform(buildings.begin(), buildings.end(), buildingAreas.begin(), getArea);
    float totalArea = std::accumulate(buildingAreas.begin(), buildingAreas.end(), 0.0);

    float averageHeight = totalVolume / totalArea;
    return averageHeight;
}

bool solutionIsFeasible(Buildings buildings, float maxAverageHeight)
{
    float averageHeight = getAverageHeight(buildings);
    bool solutionIsFeasible = averageHeight <= maxAverageHeight;
    return solutionIsFeasible;
}