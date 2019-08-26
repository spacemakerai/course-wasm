
#include <numeric>
#include "feasibilityChecker.h"

float getAverageHeight(const Buildings& buildings)
{
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
    bool solutionIsFeasible = buildingsAreWithinMinMaxHeightBounds;
    return solutionIsFeasible;
}