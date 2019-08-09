
#ifndef OPTIMIZE_SOLUTIONCANDIDATE_H
#define OPTIMIZE_SOLUTIONCANDIDATE_H
#include <vector>
#include "geometry.h"
#include "optimize.h"


struct SolutionCandidate {
    float cost;
    bool isFeasible;
    Buildings buildings;
};
typedef std::vector<SolutionCandidate> SolutionCandidates;

SolutionCandidate createSolutionCandidateFromBuildings(Buildings buildings, ObjectiveToggles objectiveToggles, float maxAverageHeight);
SolutionCandidate getBestSolutionCandidate(SolutionCandidates solutionCandidates);

#endif //OPTIMIZE_SOLUTIONCANDIDATE_H
