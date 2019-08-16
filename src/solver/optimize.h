
#ifndef OPTIMIZE_OPTIMIZE_H
#define OPTIMIZE_OPTIMIZE_H

#include "geometry.h"
#include <vector>

enum Objective {DISTANCE_TO_BUS_STOP, VOLUME};

Buildings optimizeBuildings(const Buildings& initialBuildings, Objective objective);

#endif //OPTIMIZE_OPTIMIZE_H
