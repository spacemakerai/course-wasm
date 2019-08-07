
#include "solutionCandidate.h"
#include "cost.h"


SolutionCandidate createSolutionCandidateFromBuildings(Buildings buildings, ObjectiveToggles objectiveToggles){
    float cost = getCost(buildings, objectiveToggles);
    bool solutionIsFeasible = true;
    SolutionCandidate solutionCandidate{cost, solutionIsFeasible, buildings};
    return solutionCandidate;
}