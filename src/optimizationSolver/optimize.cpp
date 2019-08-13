
#include "optimize.h"
#include "solutionCandidate.h"
#include "cost.h"
#include "feasibilityChecker.h"

float MAX_HEIGHT = 20.0;
float MIN_HEIGHT = 5.0;
float HEIGHT_INCREMENT = 1.0;
float MAX_AVERAGE_HEIGHT = 18;

SolutionCandidates increaseAndDecreaseHeightOfBuilding(int buildingIndexToChange, Buildings buildings, ObjectiveToggles objectiveToggles);
SolutionCandidates getFeasibleSolutionCandidates(SolutionCandidates solutionCandidates);
void addSolutionCandidatesToList(SolutionCandidates *listToBeAddedTo, SolutionCandidates solutionCandidatesToAdd);


Buildings optimizeBuildings(Buildings initialBuildings, ObjectiveToggles objectiveToggles)
{
    SolutionCandidates solutionCandidates;
    SolutionCandidate initialSolutionCandidate{createSolutionCandidateFromBuildings(initialBuildings, objectiveToggles, MAX_AVERAGE_HEIGHT)};
    solutionCandidates.push_back(initialSolutionCandidate);

    int numberOfBuildings = int (initialBuildings.size());

    for (int buildingIndex = 0; buildingIndex < numberOfBuildings; buildingIndex += 1)
    {
        SolutionCandidates solutionsWithOneBuildingHeightChanged = increaseAndDecreaseHeightOfBuilding(buildingIndex, initialBuildings, objectiveToggles);
        addSolutionCandidatesToList(&solutionCandidates, solutionsWithOneBuildingHeightChanged);

        for (SolutionCandidate solutionCandidate: solutionsWithOneBuildingHeightChanged)
        {
            for (int otherBuildingIndex = buildingIndex + 1; otherBuildingIndex < numberOfBuildings; otherBuildingIndex += 1)
            {
                SolutionCandidates solutionsWithTwoBuildingHeightsChanged = increaseAndDecreaseHeightOfBuilding(otherBuildingIndex, solutionCandidate.buildings, objectiveToggles);
                addSolutionCandidatesToList(&solutionCandidates, solutionsWithTwoBuildingHeightsChanged);
            }
        }
    }
    SolutionCandidates feasibleSolutionCandidates = getFeasibleSolutionCandidates(solutionCandidates);
    SolutionCandidate bestSolutionCandidate = getBestSolutionCandidate(feasibleSolutionCandidates);
    return bestSolutionCandidate.buildings;
}

void addSolutionCandidatesToList(SolutionCandidates *listToBeAddedTo, SolutionCandidates solutionCandidatesToAdd)
{
    for (SolutionCandidate solutionCandidateToAdd: solutionCandidatesToAdd)
    {
        listToBeAddedTo->push_back(solutionCandidateToAdd);
    }
}

Buildings changeHeightOfBuilding(Buildings buildings, int buildingIndexToChange, float heightIncrement)
{
    Buildings updatedBuildings = buildings;
    updatedBuildings[buildingIndexToChange].height = buildings[buildingIndexToChange].height + heightIncrement;
    return updatedBuildings;
}

SolutionCandidates getFeasibleSolutionCandidates(SolutionCandidates solutionCandidates)
{
    SolutionCandidates feasibleSolutionCandidates;
    for (SolutionCandidate solutionCandidate: solutionCandidates)
    {
        if (solutionCandidate.isFeasible)
        {
            feasibleSolutionCandidates.push_back(solutionCandidate);
        }
    }
    return feasibleSolutionCandidates;
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
