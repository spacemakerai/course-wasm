
#include <numeric>
#include "feasibilityChecker.h"

float getAverageHeight(const Buildings& buildings)
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

bool checkIfBuildingWithinHeightRange(const Buildings& buildings, float minHeight, float maxHeight)
{
    for (const Building& building: buildings)
    {
        if (building.height < minHeight)
        {
            return false;
        }
        if (building.height > maxHeight)
        {
            return false;
        }
    }
    return true;
}

bool solutionIsFeasible(const Buildings& buildings, float maxAverageHeight, float minHeight, float maxHeight)
{
    bool buildingsAreWithinMinMaxHeightBounds = checkIfBuildingWithinHeightRange(buildings, minHeight, maxHeight);
    float averageHeight = getAverageHeight(buildings);
    bool averageBuildingHeightIsBelowCriticalLimit = averageHeight <= maxAverageHeight;
    bool solutionIsFeasible = averageBuildingHeightIsBelowCriticalLimit && buildingsAreWithinMinMaxHeightBounds;
    return solutionIsFeasible;
}