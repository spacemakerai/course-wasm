
#include <numeric>
#include "cost.h"

float getTotalVolume(Buildings buildings);


float getCost(Buildings buildings,ObjectiveToggles objectiveToggles)
{
    float cost = 0;
    if (objectiveToggles.volume) {
        float volume = getTotalVolume(buildings);
        cost += volume;
    }
    if (objectiveToggles.sun){
        float sunCost = 0;
        cost += sunCost;
    }
    return cost;
}


float getTotalVolume(Buildings buildings)
{
    std::vector<float> buildingVolumes;
    buildingVolumes.resize(buildings.size());
    std::transform(buildings.begin(), buildings.end(), buildingVolumes.begin(), getVolume);
    float totalVolume = std::accumulate(buildingVolumes.begin(), buildingVolumes.end(), 0.0);
    return totalVolume;
}