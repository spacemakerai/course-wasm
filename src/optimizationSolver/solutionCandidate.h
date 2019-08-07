
#ifndef OPTIMIZE_SOLUTIONCANDIDATE_H
#define OPTIMIZE_SOLUTIONCANDIDATE_H
#include <vector>
#include "geometry.h"
#include "optimize.h"


struct SolutionCandidate {
    float cost;
    bool violation;
    std::vector<float> heights;
};
typedef std::vector<SolutionCandidate> SolutionCandidates;

SolutionCandidate createSolutionCandidateFromBuildings(Buildings buildings, ObjectiveToggles objectiveToggles);

#endif //OPTIMIZE_SOLUTIONCANDIDATE_H
