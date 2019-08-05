//
// Created by Kristine Hagen on 2019-08-05.
//

#include <numeric>
#include "cost.h"


double getCost(std::vector<Building> buildings, bool volumeToggle, bool sunToggle){
    double cost = 0;
    if (volumeToggle) {
        std::vector<double> buildingAreas;
        buildingAreas.reserve(buildings.size());
        std::transform(buildings.begin(), buildings.end(), buildingAreas.begin(), simpleArea);
        double totalArea = std::accumulate(buildingAreas.begin(), buildingAreas.end(), 0.0);
        cost += totalArea;
    }
    if (sunToggle){
        double sunCost = 0;
        cost += sunCost;
    }
    return cost;
}