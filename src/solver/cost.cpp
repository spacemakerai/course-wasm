
#include <numeric>
#include <algorithm>
#include "cost.h"

float getTotalVolume(const Buildings& buildings);


float getDistanceToBusStop(const Buildings &vector, Point busStopCoordinate, float volume);

float getCost(const Buildings& buildings, ObjectiveToggles objectiveToggles, Point busStopCoordinate)
{
    float cost = 0;
    float volume = getTotalVolume(buildings);
    if (objectiveToggles.volume) {
        cost += volume;
    }
    if (objectiveToggles.distanceToBusStop){
        float distanceToBusStop = getDistanceToBusStop(buildings, busStopCoordinate, volume);
        cost += distanceToBusStop;
    }
    return cost;
}

float getDistanceToBusStop(const Buildings &buildings, Point busStopCoordinate, float totalVolume) {
    float totalDistanceToBusStopCost = 0;
    for (auto building : buildings) {
        Point buildingCentroid = getCentroid(building);
        float busStopContributionForBuilding = getVolume(building) * lengthOfLine(buildingCentroid, busStopCoordinate);
        totalDistanceToBusStopCost += busStopContributionForBuilding;
    }
    return -(totalDistanceToBusStopCost/totalVolume*10);
}


float getTotalVolume(const Buildings& buildings)
{
    std::vector<float> buildingVolumes;
    buildingVolumes.resize(buildings.size());
    std::transform(buildings.begin(), buildings.end(), buildingVolumes.begin(), getVolume);
    float totalVolume = std::accumulate(buildingVolumes.begin(), buildingVolumes.end(), 0.0);
    return totalVolume;
}