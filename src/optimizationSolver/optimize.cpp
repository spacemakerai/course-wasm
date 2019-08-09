
#include "optimize.h"
#include "solutionCandidate.h"
#include "cost.h"
#include "feasibilityChecker.h"

float MAX_HEIGHT = 20.0;
float MIN_HEIGHT = 5.0;
float HEIGHT_INCREMENT = 1.0;
float MAX_AVERAGE_HEIGHT = 10;

SolutionCandidates createSolutionCandidatesByChangingOneBuildingHeight(int buildingIndexToChange, Buildings buildings, ObjectiveToggles objectiveToggles);
void addFeasibleSolutionCandidatesToSolutionCandidateList(SolutionCandidates solutionCandidates, SolutionCandidates potentialSolutionCandidates);


Buildings optimizeBuildings(Buildings initialBuildings, ObjectiveToggles objectiveToggles)
{
    SolutionCandidates solutionCandidates;
    solutionCandidates.push_back({createSolutionCandidateFromBuildings(initialBuildings, objectiveToggles)});

    for (int buildingIndex = 0; buildingIndex < int (initialBuildings.size()); buildingIndex += 1)
    {
        SolutionCandidates potentialSolutionCandidates = createSolutionCandidatesByChangingOneBuildingHeight(buildingIndex, initialBuildings, objectiveToggles);
        addFeasibleSolutionCandidatesToSolutionCandidateList(solutionCandidates, potentialSolutionCandidates);
    }
    SolutionCandidate bestSolutionCandidate = getBestSolutionCandidate(solutionCandidates);
    return bestSolutionCandidate.buildings;
}

SolutionCandidates createSolutionCandidatesByChangingOneBuildingHeight(int buildingIndexToChange, Buildings buildings, ObjectiveToggles objectiveToggles)
{
    SolutionCandidates potentialSolutionCandidates;

    float currentHeight = buildings[buildingIndexToChange].height;
    if (currentHeight <= MAX_HEIGHT + HEIGHT_INCREMENT)
    {
        Buildings updatedBuildings = buildings;
        updatedBuildings[buildingIndexToChange].height = currentHeight + HEIGHT_INCREMENT;
        if (solutionIsFeasible(updatedBuildings, MAX_AVERAGE_HEIGHT)){
            SolutionCandidate solutionCandidateFromUpdatedBuildings = createSolutionCandidateFromBuildings(updatedBuildings, objectiveToggles);
            potentialSolutionCandidates.push_back(solutionCandidateFromUpdatedBuildings);
        }
    }
    if (currentHeight >= MIN_HEIGHT - HEIGHT_INCREMENT)
    {
        Buildings updatedBuildings = buildings;
        updatedBuildings[buildingIndexToChange].height = currentHeight - HEIGHT_INCREMENT;
        if (solutionIsFeasible(updatedBuildings, MAX_AVERAGE_HEIGHT)) {
            SolutionCandidate solutionCandidateFromUpdatedBuildings = createSolutionCandidateFromBuildings(updatedBuildings, objectiveToggles);
            potentialSolutionCandidates.push_back(solutionCandidateFromUpdatedBuildings);
        }
    }
    return potentialSolutionCandidates;
}


void addFeasibleSolutionCandidatesToSolutionCandidateList(SolutionCandidates solutionCandidates, SolutionCandidates potentialSolutionCandidates)
{
    for (SolutionCandidate potentialSolutionCandidate: potentialSolutionCandidates)
    {
        if (potentialSolutionCandidate.solutionIsFeasible)
        {
            solutionCandidates.push_back(potentialSolutionCandidate);
        }
    }
}


