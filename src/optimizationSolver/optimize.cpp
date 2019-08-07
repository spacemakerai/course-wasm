
#include "optimize.h"
#include "solutionCandidate.h"

Buildings optimizeBuildings(Buildings initialBuildings, ObjectiveToggles objectiveToggles){
    SolutionCandidates solution_candidates;
    SolutionCandidate currentSolutionCandidate = createSolutionCandidateFromBuildings(initialBuildings, objectiveToggles);
    solution_candidates.push_back(currentSolutionCandidate);
    return initialBuildings;
}

Buildings increaseHeightOfBuildings(Buildings initialBuildings){
    Buildings buildingsWithIncreasedHeight;
    for (Building building: initialBuildings) {
        Building buildingWithIncreasedHeight { building.height + 1, building.ground_polygon };
        buildingsWithIncreasedHeight.push_back(buildingWithIncreasedHeight);
    }
    return buildingsWithIncreasedHeight;
}