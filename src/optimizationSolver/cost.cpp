
#include <numeric>
#include "cost.h"


float getCost(Buildings buildings,ObjectiveToggles objectiveToggles){
    float cost = 0;
    if (objectiveToggles.volume) {
        std::vector<float> buildingVolumes;
        buildingVolumes.resize(buildings.size());
        std::transform(buildings.begin(), buildings.end(), buildingVolumes.begin(), simpleVolume);
        float totalVolume = std::accumulate(buildingVolumes.begin(), buildingVolumes.end(), 0.0);
        cost += totalVolume;
    }
    if (objectiveToggles.sun){
        float sunCost = 0;
        cost += sunCost;
    }
    return cost;
}