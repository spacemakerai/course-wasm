//
// Created by Kristine Hagen on 2019-08-05.
//

#include "optimize.h"
#include "solutionCandidate.h"

std::vector<Building> optimizeBuildings(std::vector<Building> initialBuildings, bool volumeToggle, bool sunToggle){
    SolutionCandidates solution_candidates;
    SolutionCandidate currentSolutionCandidate = createSolutionCandidateFromBuildings(initialBuildings, volumeToggle, sunToggle);
    solution_candidates.push_back(currentSolutionCandidate);
    return initialBuildings;
}