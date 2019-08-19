
#include <numeric>
#include "feasibilityChecker.h"
float MAX_HEIGHT = 20.0;
float MIN_HEIGHT = 5.0;

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

bool checkIfBuildingsComplyWithMinMaxHeightBounds(const Buildings& buildings)
{
    for (const Building& building: buildings)
    {
        if (building.height < MIN_HEIGHT)
        {
            return false;
        }
        if (building.height > MAX_HEIGHT)
        {
            return false;
        }
    }
    return true;
}

bool solutionIsFeasible(const Buildings& buildings, float maxAverageHeight)
{
    bool buildingsAreWithinMinMaxHeightBounds = checkIfBuildingsComplyWithMinMaxHeightBounds(buildings);
    float averageHeight = getAverageHeight(buildings);
    bool averageBuildingHeightIsBelowCriticalLimit = averageHeight <= maxAverageHeight;
    bool solutionIsFeasible = averageBuildingHeightIsBelowCriticalLimit && buildingsAreWithinMinMaxHeightBounds;
    return solutionIsFeasible;
}