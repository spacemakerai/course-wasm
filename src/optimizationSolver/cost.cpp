
#include <numeric>
#include "cost.h"


float getCost(Buildings buildings,ObjectiveToggles objectiveToggles){
    float cost = 0;
    if (objectiveToggles.volume) {
        std::vector<float> buildingAreas;
        buildingAreas.reserve(buildings.size());
        std::transform(buildings.begin(), buildings.end(), buildingAreas.begin(), simpleArea);
        float totalArea = std::accumulate(buildingAreas.begin(), buildingAreas.end(), 0.0);
        cost += totalArea;
    }
    if (objectiveToggles.sun){
        float sunCost = 0;
        cost += sunCost;
    }
    return cost;
}