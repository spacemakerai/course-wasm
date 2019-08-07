
#ifndef OPTIMIZE_COST_H
#define OPTIMIZE_COST_H
#include <vector>
#include "geometry.h"
#include "optimize.h"
#include "solutionCandidate.h"


float getCost(Buildings buildings, ObjectiveToggles objectiveToggles);
SolutionCandidate getBestSolutionCandidate(SolutionCandidates solutionCandidates);

#endif //OPTIMIZE_COST_H
