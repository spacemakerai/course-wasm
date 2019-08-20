
#include <numeric>
#include <algorithm>
#include "objective.h"

float getTotalVolume(const Buildings& buildings);


float getDistanceToBusStopObjectiveValue(const Buildings &buildings, Point busStopCoordinate);

float getObjectiveValue(const Buildings& buildings, Objective objective, Point busStopCoordinate)
{
    float objectiveValue = 0;
    if (objective == Objective::VOLUME) {
        float volume = getTotalVolume(buildings);
        objectiveValue = volume;
    }
    else if (objective == Objective::DISTANCE_TO_BUS_STOP){
        objectiveValue = getDistanceToBusStopObjectiveValue(buildings, busStopCoordinate);
    }
    return objectiveValue;
}

float getDistanceToBusStopObjectiveValue(const Buildings &buildings, Point busStopCoordinate) {
    float totalVolume = 0;
    float totalDistanceToBusStopObjectiveValue = 0;
    for (const Building& building : buildings) {
        Point buildingCentroid = getCentroid(building.groundPolygon);
        float buildingVolume = getVolume(building);
        totalVolume += buildingVolume;
        float busStopContributionForBuilding = buildingVolume * lengthOfLine(buildingCentroid, busStopCoordinate);
        totalDistanceToBusStopObjectiveValue += busStopContributionForBuilding;
    }
    return -(totalDistanceToBusStopObjectiveValue / totalVolume);
}


float getTotalVolume(const Buildings& buildings)
{
    std::vector<float> buildingVolumes;
    buildingVolumes.resize(buildings.size());
    std::transform(buildings.begin(), buildings.end(), buildingVolumes.begin(), getVolume);
    float totalVolume = std::accumulate(buildingVolumes.begin(), buildingVolumes.end(), 0.0);
    return totalVolume;
}