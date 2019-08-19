
#ifndef OPTIMIZE_OBJECTIVE_H
#define OPTIMIZE_OBJECTIVE_H
#include <vector>
#include "geometry.h"
#include "optimize.h"
#include "solutionCandidate.h"


float getObjectiveValue(const Buildings& buildings, Objective objective, Point busStopCoordinate);


#endif //OPTIMIZE_OBJECTIVE_H
