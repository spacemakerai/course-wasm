
#include "optimize.h"
#include "solutionCandidate.h"
#include "cost.h"
#include "feasibilityChecker.h"

float MAX_HEIGHT = 20.0;
float MIN_HEIGHT = 5.0;
float HEIGHT_INCREMENT = 1.0;
float MAX_AVERAGE_HEIGHT = 10;


Buildings optimizeBuildings(Buildings initialBuildings, ObjectiveToggles objectiveToggles)
{
    SolutionCandidates solutionCandidates;
    solutionCandidates.push_back({createSolutionCandidateFromBuildings(initialBuildings, objectiveToggles)});

    for (int buildingIndex = 0; buildingIndex < int (initialBuildings.size()); buildingIndex += 1)
    {
        float currentHeight = initialBuildings[buildingIndex].height;

        if (currentHeight <= MAX_HEIGHT + HEIGHT_INCREMENT)
        {
            Buildings updatedBuildings = initialBuildings;
            updatedBuildings[buildingIndex].height = currentHeight + HEIGHT_INCREMENT;
            if (solutionIsFeasible(updatedBuildings, MAX_AVERAGE_HEIGHT)){
                solutionCandidates.push_back({createSolutionCandidateFromBuildings(updatedBuildings, objectiveToggles)});
            }
        }
        if (currentHeight >= MIN_HEIGHT - HEIGHT_INCREMENT)
        {
            Buildings updatedBuildings = initialBuildings;
            updatedBuildings[buildingIndex].height = currentHeight - HEIGHT_INCREMENT;
            if (solutionIsFeasible(updatedBuildings, MAX_AVERAGE_HEIGHT)) {
                solutionCandidates.push_back({createSolutionCandidateFromBuildings(updatedBuildings, objectiveToggles)});
            }
        }
    }
    SolutionCandidate bestSolutionCandidate = getBestSolutionCandidate(solutionCandidates);
    return bestSolutionCandidate.buildings;
}