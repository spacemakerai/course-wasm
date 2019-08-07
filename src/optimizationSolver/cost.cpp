//
// Created by Kristine Hagen on 2019-08-05.
//

#include <numeric>
#include "cost.h"


float getCost(std::vector<Building> buildings, bool volumeToggle, bool sunToggle){
    float cost = 0;
    if (volumeToggle) {
        std::vector<float> buildingAreas;
        buildingAreas.reserve(buildings.size());
        std::transform(buildings.begin(), buildings.end(), buildingAreas.begin(), simpleArea);
        float totalArea = std::accumulate(buildingAreas.begin(), buildingAreas.end(), 0.0);
        cost += totalArea;
    }
    if (sunToggle){
        float sunCost = 0;
        cost += sunCost;
    }
    return cost;
}