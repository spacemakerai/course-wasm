//
// Created by Kristine Hagen on 2019-08-05.
//

#ifndef OPTIMIZE_OPTIMIZE_H
#define OPTIMIZE_OPTIMIZE_H

#include "geometry.h"
#include <vector>

std::vector<Building> optimizeBuildings(std::vector<Building> initialBuildings, bool volumeToggle, bool sunToggle);

#endif //OPTIMIZE_OPTIMIZE_H
