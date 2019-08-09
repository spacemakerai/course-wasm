
#include "optimize.h"
#include "solutionCandidate.h"
#include "cost.h"
#include "feasibilityChecker.h"

float MAX_HEIGHT = 20.0;
float MIN_HEIGHT = 5.0;
float HEIGHT_INCREMENT = 1.0;
float MAX_AVERAGE_HEIGHT = 18;

SolutionCandidates increaseAndDecreaseHeightOfBuilding(int buildingIndexToChange, Buildings buildings, ObjectiveToggles objectiveToggles);
void addFeasibleSolutionCandidatesToSolutionCandidateList(SolutionCandidates *solutionCandidates, SolutionCandidates potentialSolutionCandidates);


Buildings optimizeBuildings(Buildings initialBuildings, ObjectiveToggles objectiveToggles)
{
    SolutionCandidates solutionCandidates;
    solutionCandidates.push_back({createSolutionCandidateFromBuildings(initialBuildings, objectiveToggles, MAX_AVERAGE_HEIGHT)});

    for (int buildingIndex = 0; buildingIndex < int (initialBuildings.size()); buildingIndex += 1)
    {
        SolutionCandidates potentialSolutionCandidates = increaseAndDecreaseHeightOfBuilding(buildingIndex, initialBuildings, objectiveToggles);
        addFeasibleSolutionCandidatesToSolutionCandidateList(&solutionCandidates, potentialSolutionCandidates);
    }
    SolutionCandidate bestSolutionCandidate = getBestSolutionCandidate(solutionCandidates);
    return bestSolutionCandidate.buildings;
}


Buildings changeHeightOfBuilding(Buildings buildings, int buildingIndexToChange, float heightIncrement)
{
    float currentHeight = buildings[buildingIndexToChange].height;
    Buildings updatedBuildings = buildings;
    updatedBuildings[buildingIndexToChange].height = currentHeight + heightIncrement;
    return updatedBuildings;
}


SolutionCandidates increaseAndDecreaseHeightOfBuilding(int buildingIndexToChange, Buildings buildings, ObjectiveToggles objectiveToggles)
{
    SolutionCandidates potentialSolutionCandidates;
    float currentHeight = buildings[buildingIndexToChange].height;
    if (currentHeight <= MAX_HEIGHT + HEIGHT_INCREMENT)
    {
        Buildings buildingsWithIncreasedHeight = changeHeightOfBuilding(buildings, buildingIndexToChange, HEIGHT_INCREMENT);
        potentialSolutionCandidates.push_back({createSolutionCandidateFromBuildings(buildingsWithIncreasedHeight, objectiveToggles, MAX_AVERAGE_HEIGHT)});
    }
    if (currentHeight >= MIN_HEIGHT - HEIGHT_INCREMENT)
    {
        Buildings buildingsWithIncreasedHeight = changeHeightOfBuilding(buildings, buildingIndexToChange, -HEIGHT_INCREMENT);
        potentialSolutionCandidates.push_back({createSolutionCandidateFromBuildings(buildingsWithIncreasedHeight, objectiveToggles, MAX_AVERAGE_HEIGHT)});
    }
    return potentialSolutionCandidates;
}


void addFeasibleSolutionCandidatesToSolutionCandidateList(SolutionCandidates *solutionCandidates, SolutionCandidates potentialSolutionCandidates)
{
    for (SolutionCandidate potentialSolutionCandidate: potentialSolutionCandidates)
    {
        if (potentialSolutionCandidate.isFeasible)
        {
            solutionCandidates->push_back(potentialSolutionCandidate);
        }
    }
}


