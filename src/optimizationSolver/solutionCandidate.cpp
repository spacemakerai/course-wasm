
#include "solutionCandidate.h"
#include "cost.h"


SolutionCandidate createSolutionCandidateFromBuildings(Buildings buildings, ObjectiveToggles objectiveToggles){
    float cost = getCost(buildings, objectiveToggles);
    std::vector<float> heights;
    heights.resize(buildings.size());
    std::transform(buildings.begin(), buildings.end(), heights.begin(), getHeight);
    SolutionCandidate solutionCandidate{cost, true, heights};
    return solutionCandidate;
}