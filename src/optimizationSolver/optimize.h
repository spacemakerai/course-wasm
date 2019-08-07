
#ifndef OPTIMIZE_OPTIMIZE_H
#define OPTIMIZE_OPTIMIZE_H

#include "geometry.h"
#include <vector>

std::vector<Building> optimizeBuildings(std::vector<Building> initialBuildings, bool volumeToggle, bool sunToggle);
std::vector<Building> increaseHeightOfBuildings(std::vector<Building> initialBuildings);

#endif //OPTIMIZE_OPTIMIZE_H
