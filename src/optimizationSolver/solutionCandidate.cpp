
#include "solutionCandidate.h"
#include "cost.h"


SolutionCandidate createSolutionCandidateFromBuildings(std::vector<Building> buildings, bool volumeToggle, bool sunToggle){
    float cost = getCost(buildings, volumeToggle, sunToggle);
    std::vector<float> heights;
    heights.resize(buildings.size());
    std::transform(buildings.begin(), buildings.end(), heights.begin(), getHeight);
    SolutionCandidate solutionCandidate{cost, true, heights};
    return solutionCandidate;
}