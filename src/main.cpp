#include <vector>
#define WASM_EXPORT __attribute__((visibility("default")))
#include<cmath>
#include <numeric>


WASM_EXPORT
void move(unsigned char* positions, int n) {
  for (int i=0; i<n; i+=3) {
    positions[i] += 3;
    positions[i+1] += 2;
    positions[i+2] += 1;
  }
}


struct Point {
    double x;
    double y;
};

typedef std::vector<Point> Polygon;

struct Building {
    double start_z;
    double end_z;
    Polygon ground_polygon;
};

struct SolutionCandidate {
    double cost;
    bool violation;
    std::vector<double> heights;
};

typedef std::vector<SolutionCandidate> SolutionCandidates;


double lengthOfLine(Point point1, Point point2){
    double distance = sqrt(pow(point1.x - point2.x, 2) + pow(point1.y-point2.y,2));
    return distance;
}

double simpleArea(Building building){
    Polygon rectangularPolygon = building.ground_polygon;
    double length = lengthOfLine(rectangularPolygon[0], rectangularPolygon[1]);
    double width = lengthOfLine(rectangularPolygon[1], rectangularPolygon[2]);
    return length * width;
}

double getCost(std::vector<Building> buildings, bool volumeToggle, bool sunToggle){
    double cost = 0;
    if (volumeToggle) {
        std::vector<double> buildingAreas;
        buildingAreas.reserve(buildings.size());
        std::transform(buildings.begin(), buildings.end(), buildingAreas.begin(), simpleArea);
        double totalArea = std::accumulate(buildingAreas.begin(), buildingAreas.end(), 0.0);
        cost += totalArea;
    }
    if (sunToggle){
        double sunCost = 0;
        cost += sunCost;
    }
    return cost;
}

double getHeight(Building building) { return building.end_z - building.start_z; };

SolutionCandidate createSolutionCandidateFromBuildings(std::vector<Building> buildings, bool volumeToggle, bool sunToggle){
    double cost = getCost(buildings, volumeToggle, sunToggle);
    std::vector<double> heights;
    heights.reserve(buildings.size());
    std::transform(buildings.begin(), buildings.end(), heights, getHeight);
    SolutionCandidate solutionCandidate{cost, true, heights};
    return solutionCandidate;
}


SolutionCandidates solution_candidates;

std::vector<Building> solver(std::vector<Building> buildings) {
    SolutionCandidate currentSolutionCandidate = createSolutionCandidateFromBuildings(buildings, true, false);
    solution_candidates.push_back(currentSolutionCandidate);

}

int main(int argc, char *argv[]) {

}

