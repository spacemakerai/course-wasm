
#include "solutionCandidate.h"
#include "cost.h"


SolutionCandidate createSolutionCandidateFromBuildings(Buildings buildings, ObjectiveToggles objectiveToggles)
{
    float cost = getCost(buildings, objectiveToggles);
    bool solutionIsFeasible = true;
    return {cost, solutionIsFeasible, buildings};
}