
#ifndef OPTIMIZE_OPTIMIZE_H
#define OPTIMIZE_OPTIMIZE_H

#include "geometry.h"
#include <vector>

struct ObjectiveToggles {
    bool sun;
    bool volume;
};

Buildings optimizeBuildings(Buildings initialBuildings, ObjectiveToggles objectiveToggles);
Buildings increaseHeightOfBuildings(Buildings initialBuildings);

#endif //OPTIMIZE_OPTIMIZE_H
