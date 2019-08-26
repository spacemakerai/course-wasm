
#include "optimize.h"
#include "solutionCandidate.h"
#include "objective.h"
#include "feasibilityChecker.h"

float HEIGHT_INCREMENT = 1.0;
float MAX_AVERAGE_HEIGHT = 18;
Point BUS_STOP_COORDINATE{100, 100};
float MAX_HEIGHT = 20.0;
float MIN_HEIGHT = 5.0;

SolutionCandidates increaseAndDecreaseHeightOfBuilding(int buildingIndexToChange, const Buildings& buildings, Objective objective);
SolutionCandidates getFeasibleSolutionCandidates(const SolutionCandidates& solutionCandidates);
void addSolutionCandidatesToList(SolutionCandidates& listToBeAddedTo, const SolutionCandidates& solutionCandidatesToAdd);


Buildings optimizeBuildings(const Buildings& initialBuildings, Objective objective)
{
    SolutionCandidates solutions;
    SolutionCandidate initialSolution{createSolutionFromBuildings(initialBuildings, objective, MAX_AVERAGE_HEIGHT, BUS_STOP_COORDINATE, MIN_HEIGHT, MAX_HEIGHT)};
    solutions.push_back(initialSolution);

    int numberOfBuildings = int (initialBuildings.size());

    for (int buildingIndex = 0; buildingIndex < numberOfBuildings; buildingIndex += 1)
    {
        SolutionCandidates solutionsWithOneBuildingHeightChanged = increaseAndDecreaseHeightOfBuilding(buildingIndex, initialBuildings, objective);
        addSolutionCandidatesToList(solutions, solutionsWithOneBuildingHeightChanged);

        for (const SolutionCandidate& solutionCandidate: solutionsWithOneBuildingHeightChanged)
        {
            for (int otherBuildingIndex = buildingIndex + 1; otherBuildingIndex < numberOfBuildings; otherBuildingIndex += 1)
            {
                SolutionCandidates solutionsWithTwoBuildingHeightsChanged = increaseAndDecreaseHeightOfBuilding(otherBuildingIndex, solutionCandidate.buildings, objective);
                addSolutionCandidatesToList(solutions, solutionsWithTwoBuildingHeightsChanged);
            }
        }
    }
    SolutionCandidates feasibleSolutionCandidates = getFeasibleSolutionCandidates(solutions);
    SolutionCandidate bestSolutionCandidate = getBestSolutionCandidate(feasibleSolutionCandidates);
    return bestSolutionCandidate.buildings;
}

void addSolutionCandidatesToList(SolutionCandidates& listToBeAddedTo, const SolutionCandidates& solutionCandidatesToAdd)
{
    for (const SolutionCandidate& solutionCandidateToAdd: solutionCandidatesToAdd)
    {
        listToBeAddedTo.push_back(solutionCandidateToAdd);
    }
}

Buildings changeHeightOfBuilding(Buildings buildings, int buildingIndexToChange, float heightIncrement)
{
    Buildings updatedBuildings = buildings;
    updatedBuildings[buildingIndexToChange].height = buildings[buildingIndexToChange].height + heightIncrement;
    return updatedBuildings;
}

SolutionCandidates getFeasibleSolutionCandidates(const SolutionCandidates& solutionCandidates)
{
    SolutionCandidates feasibleSolutionCandidates;
    for (const SolutionCandidate& solutionCandidate: solutionCandidates)
    {
        if (solutionCandidate.isFeasible)
        {
            feasibleSolutionCandidates.push_back(solutionCandidate);
        }
    }
    return feasibleSolutionCandidates;
}


SolutionCandidates increaseAndDecreaseHeightOfBuilding(int buildingIndexToChange, const Buildings& buildings, Objective objective)
{
    SolutionCandidates solutionCandidates;

    Buildings buildingsWithIncreasedHeight = changeHeightOfBuilding(buildings, buildingIndexToChange, HEIGHT_INCREMENT);
    SolutionCandidate solutionWithIncreasedBuildingHeight = createSolutionFromBuildings(buildingsWithIncreasedHeight, objective, MAX_AVERAGE_HEIGHT, BUS_STOP_COORDINATE, MIN_HEIGHT, MAX_HEIGHT);
    solutionCandidates.push_back(solutionWithIncreasedBuildingHeight);

    Buildings buildingsWithDecreasedHeight = changeHeightOfBuilding(buildings, buildingIndexToChange, -HEIGHT_INCREMENT);
    SolutionCandidate solutionWithDecreasedBuildingHeight = createSolutionFromBuildings(buildingsWithDecreasedHeight, objective, MAX_AVERAGE_HEIGHT, BUS_STOP_COORDINATE, MIN_HEIGHT, MAX_HEIGHT);
    solutionCandidates.push_back(solutionWithDecreasedBuildingHeight);

    return solutionCandidates;
}
