//
// Created by Kristine Hagen on 2019-08-05.
//
#ifndef OPTIMIZE_SOLUTIONCANDIDATE_H
#define OPTIMIZE_SOLUTIONCANDIDATE_H
#include <vector>
#include "geometry.h"


struct SolutionCandidate {
    double cost;
    bool violation;
    std::vector<double> heights;
};
typedef std::vector<SolutionCandidate> SolutionCandidates;

SolutionCandidate createSolutionCandidateFromBuildings(std::vector<Building> buildings, bool volumeToggle, bool sunToggle);

#endif //OPTIMIZE_SOLUTIONCANDIDATE_H
