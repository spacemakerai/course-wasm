
#include <numeric>
#include <algorithm>
#include "cost.h"

float getTotalVolume(const Buildings& buildings);


float getDistanceToBusStop(const Buildings &buildings, Point busStopCoordinate);

float getCost(const Buildings& buildings, Objective objective, Point busStopCoordinate)
{
    float cost = 0;
    if (objective == Objective::VOLUME) {
        cost = 0;
    }
    else if (objective == Objective::DISTANCE_TO_BUS_STOP){
        cost = getDistanceToBusStop(buildings, busStopCoordinate);
    }
    return cost;
}

float getDistanceToBusStop(const Buildings &buildings, Point busStopCoordinate) {
    float totalVolume = 0;
    float totalDistanceToBusStopCost = 0;
    for (const Building& building : buildings) {
        Point buildingCentroid = getCentroid(building.groundPolygon);
        float buildingVolume = getVolume(building);
        totalVolume += buildingVolume;
        float busStopContributionForBuilding = buildingVolume * lengthOfLine(buildingCentroid, busStopCoordinate);
        totalDistanceToBusStopCost += busStopContributionForBuilding;
    }
    return -(totalDistanceToBusStopCost/totalVolume);
}


float getTotalVolume(const Buildings& buildings)
{
    std::vector<float> buildingVolumes;
    buildingVolumes.resize(buildings.size());
    std::transform(buildings.begin(), buildings.end(), buildingVolumes.begin(), getVolume);
    float totalVolume = std::accumulate(buildingVolumes.begin(), buildingVolumes.end(), 0.0);
    return totalVolume;
}