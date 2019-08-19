
#include "solutionCandidate.h"
#include "objective.h"
#include "feasibilityChecker.h"


SolutionCandidate createSolutionFromBuildings(const Buildings& buildings, Objective objective, float maxAverageHeight, Point busStopCoordinate)
{
    float objectiveValue = getObjectiveValue(buildings, objective, busStopCoordinate);
    bool isFeasible = solutionIsFeasible(buildings, maxAverageHeight);
    return {objectiveValue, isFeasible, buildings};
}

bool compareCost(const SolutionCandidate& solutionCandidate1 , const SolutionCandidate& solutionCandidate2)
{
    return (solutionCandidate2.objectiveValue > solutionCandidate1.objectiveValue);
}

SolutionCandidate getBestSolutionCandidate(SolutionCandidates solutionCandidates)
{
    std::vector<SolutionCandidate>::iterator bestCandidate;
    bestCandidate = std::max_element(solutionCandidates.begin(), solutionCandidates.end(), compareCost);
    return *bestCandidate;
}