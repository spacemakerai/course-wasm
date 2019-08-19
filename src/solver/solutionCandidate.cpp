
#include "solutionCandidate.h"
#include "cost.h"
#include "feasibilityChecker.h"


SolutionCandidate createSolutionFromBuildings(const Buildings& buildings, Objective objective, float maxAverageHeight, Point busStopCoordinate)
{
    float cost = getCost(buildings, objective, busStopCoordinate);
    bool isFeasible = solutionIsFeasible(buildings, maxAverageHeight);
    return {cost, isFeasible, buildings};
}

bool compareCost(const SolutionCandidate& solutionCandidate1 , const SolutionCandidate& solutionCandidate2)
{
    return (solutionCandidate2.cost > solutionCandidate1.cost);
}

SolutionCandidate getBestSolutionCandidate(SolutionCandidates solutionCandidates)
{
    std::vector<SolutionCandidate>::iterator bestCandidate;
    bestCandidate = std::max_element(solutionCandidates.begin(), solutionCandidates.end(), compareCost);
    return *bestCandidate;
}