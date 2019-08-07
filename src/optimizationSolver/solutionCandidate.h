
#ifndef OPTIMIZE_SOLUTIONCANDIDATE_H
#define OPTIMIZE_SOLUTIONCANDIDATE_H
#include <vector>
#include "geometry.h"


struct SolutionCandidate {
    float cost;
    bool violation;
    std::vector<float> heights;
};
typedef std::vector<SolutionCandidate> SolutionCandidates;

SolutionCandidate createSolutionCandidateFromBuildings(std::vector<Building> buildings, bool volumeToggle, bool sunToggle);

#endif //OPTIMIZE_SOLUTIONCANDIDATE_H
