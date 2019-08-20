
#ifndef OPTIMIZE_FEASIBILITYCHECKER_H
#define OPTIMIZE_FEASIBILITYCHECKER_H
#include <vector>
#include "geometry.h"

bool solutionIsFeasible(const Buildings& buildings, float maxAverageHeight, float minHeight, float maxHeight);

#endif //OPTIMIZE_FEASIBILITYCHECKER_H
