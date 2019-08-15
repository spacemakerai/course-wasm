
#ifndef OPTIMIZE_COST_H
#define OPTIMIZE_COST_H
#include <vector>
#include "geometry.h"
#include "optimize.h"
#include "solutionCandidate.h"


float getCost(const Buildings& buildings, Objective objective, Point busStopCoordinate);


#endif //OPTIMIZE_COST_H
