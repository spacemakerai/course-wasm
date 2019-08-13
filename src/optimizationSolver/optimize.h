
#ifndef OPTIMIZE_OPTIMIZE_H
#define OPTIMIZE_OPTIMIZE_H

#include "geometry.h"
#include <vector>

struct ObjectiveToggles {
    bool sun;
    bool volume;
};

Buildings optimizeBuildings(const Buildings& initialBuildings, ObjectiveToggles objectiveToggles);

#endif //OPTIMIZE_OPTIMIZE_H
