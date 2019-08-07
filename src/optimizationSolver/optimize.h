
#ifndef OPTIMIZE_OPTIMIZE_H
#define OPTIMIZE_OPTIMIZE_H

#include "geometry.h"
#include <vector>

struct ObjectiveToggles {
    bool sun;
    bool volume;
};

std::vector<Building> optimizeBuildings(std::vector<Building> initialBuildings, ObjectiveToggles objectiveToggles);
std::vector<Building> increaseHeightOfBuildings(std::vector<Building> initialBuildings);

#endif //OPTIMIZE_OPTIMIZE_H
