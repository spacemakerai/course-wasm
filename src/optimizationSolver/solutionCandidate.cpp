
#include "solutionCandidate.h"
#include "cost.h"
#include "feasibilityChecker.h"


SolutionCandidate createSolutionCandidateFromBuildings(Buildings buildings, ObjectiveToggles objectiveToggles, float maxAverageHeight)
{
    float cost = getCost(buildings, objectiveToggles);
    bool isFeasible = solutionIsFeasible(buildings, maxAverageHeight);
    return {cost, isFeasible, buildings};
}

bool compareCost(SolutionCandidate solutionCandidate1 , SolutionCandidate solutionCandidate2)
{
    return (solutionCandidate1.cost < solutionCandidate2.cost);
}

SolutionCandidate getBestSolutionCandidate(SolutionCandidates solutionCandidates)
{
    std::vector<SolutionCandidate>::iterator bestCandidate;
    bestCandidate = std::max_element(solutionCandidates.begin(), solutionCandidates.end(), compareCost);
    return *bestCandidate;
}