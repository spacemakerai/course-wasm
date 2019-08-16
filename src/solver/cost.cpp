
#include <numeric>
#include <algorithm>
#include "cost.h"

float getTotalVolume(const Buildings& buildings);


float getDistanceToBusStop(const Buildings &vector, Point busStopCoordinate, float volume);

float getCost(const Buildings& buildings, Objective objective, Point busStopCoordinate)
{
    float cost = 0;
    float volume = getTotalVolume(buildings);
    if (objective == Objective::VOLUME) {
        cost = volume;
    }
    else if (objective == Objective::DISTANCE_TO_BUS_STOP){
        cost = getDistanceToBusStop(buildings, busStopCoordinate, volume);
    }
    return cost;
}

float getDistanceToBusStop(const Buildings &buildings, Point busStopCoordinate, float totalVolume) {
    float totalDistanceToBusStopCost = 0;
    for (auto building : buildings) {
        Point buildingCentroid = getCentroid(building.groundPolygon);
        float busStopContributionForBuilding = getVolume(building) * lengthOfLine(buildingCentroid, busStopCoordinate);
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