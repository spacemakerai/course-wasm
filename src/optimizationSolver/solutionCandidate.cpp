//
// Created by Kristine Hagen on 2019-08-05.
//

#include "solutionCandidate.h"
#include "cost.h"


SolutionCandidate createSolutionCandidateFromBuildings(std::vector<Building> buildings, bool volumeToggle, bool sunToggle){
    double cost = getCost(buildings, volumeToggle, sunToggle);
    std::vector<double> heights;
    heights.resize(buildings.size());
    std::transform(buildings.begin(), buildings.end(), heights.begin(), getHeight);
    SolutionCandidate solutionCandidate{cost, true, heights};
    return solutionCandidate;
}