
#include "optimize.h"
#include "solutionCandidate.h"
#include "cost.h"

float MAX_HEIGHT = 20.0;
float MIN_HEIGHT = 5.0;
float HEIGHT_INCREMENT = 1.0;


Buildings optimizeBuildings(Buildings initialBuildings, ObjectiveToggles objectiveToggles){
    SolutionCandidates solutionCandidates;
    SolutionCandidate currentSolutionCandidate = createSolutionCandidateFromBuildings(initialBuildings, objectiveToggles);
    solutionCandidates.push_back(currentSolutionCandidate);

    int numberOfBuildings = initialBuildings.size();
    for (int buildingIndex = 0; buildingIndex < numberOfBuildings; buildingIndex += 1) {
        float currentHeight = initialBuildings[buildingIndex].height;

        if (currentHeight <= MAX_HEIGHT + HEIGHT_INCREMENT) {
            Buildings updatedBuildings = initialBuildings;
            updatedBuildings[buildingIndex].height = currentHeight + HEIGHT_INCREMENT;
            SolutionCandidate newSolutionCandidate = createSolutionCandidateFromBuildings(updatedBuildings, objectiveToggles);
            solutionCandidates.push_back(newSolutionCandidate);
        }
        if (currentHeight >= MIN_HEIGHT - HEIGHT_INCREMENT) {
            Buildings updatedBuildings = initialBuildings;
            updatedBuildings[buildingIndex].height = currentHeight - HEIGHT_INCREMENT;
            SolutionCandidate newSolutionCandidate = createSolutionCandidateFromBuildings(updatedBuildings, objectiveToggles);
            solutionCandidates.push_back(newSolutionCandidate);
        }
    }
    SolutionCandidate bestSolutionCandidate = getBestSolutionCandidate(solutionCandidates);
    Buildings bestBuildings = bestSolutionCandidate.buildings;
    return bestBuildings;
}