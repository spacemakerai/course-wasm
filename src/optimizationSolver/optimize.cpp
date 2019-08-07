
#include "optimize.h"
#include "solutionCandidate.h"

std::vector<Building> optimizeBuildings(std::vector<Building> initialBuildings, ObjectiveToggles objectiveToggles){
    SolutionCandidates solution_candidates;
    SolutionCandidate currentSolutionCandidate = createSolutionCandidateFromBuildings(initialBuildings, objectiveToggles);
    solution_candidates.push_back(currentSolutionCandidate);
    return initialBuildings;
}

std::vector<Building> increaseHeightOfBuildings(std::vector<Building> initialBuildings){
    std::vector<Building> buildingsWithIncreasedHeight;
    for (Building building: initialBuildings) {
        Building buildingWithIncreasedHeight { building.height + 1, building.ground_polygon };
        buildingsWithIncreasedHeight.push_back(buildingWithIncreasedHeight);
    }
    return buildingsWithIncreasedHeight;
}