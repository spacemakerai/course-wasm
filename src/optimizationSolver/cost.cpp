
#include <numeric>
#include "cost.h"


float getCost(Buildings buildings,ObjectiveToggles objectiveToggles){
    float cost = 0;
    if (objectiveToggles.volume) {
        std::vector<float> buildingVolumes;
        buildingVolumes.resize(buildings.size());
        std::transform(buildings.begin(), buildings.end(), buildingVolumes.begin(), getVolume);
        float totalVolume = std::accumulate(buildingVolumes.begin(), buildingVolumes.end(), 0.0);
        cost += totalVolume;
    }
    if (objectiveToggles.sun){
        float sunCost = 0;
        cost += sunCost;
    }
    return cost;
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