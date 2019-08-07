#include <vector>
#define WASM_EXPORT __attribute__((visibility("default")))
#include "optimizationSolver/geometry.h"
#include "optimizationSolver/optimize.h"



int PARAMETERS_PER_BUILDING = 9;
int NUMBER_OF_COORDINATES_PER_BUILDING=4;

std::vector<Building> solver(std::vector<Building> initialBuildings);


std::vector<Building> convertParametersToBuildings(float* positions, int numberOfBuildings){
    std::vector<Building> inputBuildings;
    for (int i= 0; i<numberOfBuildings; i++) {
        Polygon ground_polygon;
        for (int j=0; j<NUMBER_OF_COORDINATES_PER_BUILDING; j++){
            Point point{positions[i*PARAMETERS_PER_BUILDING + j*2], positions[i*PARAMETERS_PER_BUILDING + j*2 +1]};
            ground_polygon.push_back(point);
        }
        Building building = {positions[i*PARAMETERS_PER_BUILDING + 8], ground_polygon};
        inputBuildings.push_back(building);
    }
    return inputBuildings;
}


void convertBuildingsToParameters(std::vector<Building> buildings, float *positions){
    int numberOfBuildings = (int) buildings.size();
    for (int i= 0; i<numberOfBuildings; i++) {
        Building building = buildings[i];
        for (int j=0; j<NUMBER_OF_COORDINATES_PER_BUILDING; j++){
            Point point = building.ground_polygon[j];
            positions[i*PARAMETERS_PER_BUILDING + j*2] = point.x;
            positions[i*PARAMETERS_PER_BUILDING + j*2 + 1] = point.y;
            positions[i*PARAMETERS_PER_BUILDING + 8] = building.height;
        }
    }

}

WASM_EXPORT
void move(float* positions, int n) {
    int numberOfBuildings = n/PARAMETERS_PER_BUILDING;
    std::vector<Building> inputBuildings = convertParametersToBuildings(positions, numberOfBuildings);
    std::vector<Building> optimizedBuildings = solver(inputBuildings);

    convertBuildingsToParameters(optimizedBuildings, positions);
}


std::vector<Building> solver(std::vector<Building> initialBuildings) {
    std::vector<Building> optimalBuildings = optimizeBuildings(initialBuildings, true, false);
    return optimalBuildings;
}

Polygon createMockPolygon(){
    Point point1{ 0,0 };
    Point point2{ 10,0 };
    Point point3{ 10,5 };
    Point point4{ 0,5 };
    Polygon polygon={point1, point2, point3, point4};
    return polygon;
}

int main(int argc, char *argv[]) {
    Polygon polygon = createMockPolygon();
    Building initialBuilding{ 9, polygon };
    std::vector<Building> initialBuildings{ {initialBuilding} };
    std::vector<Building> optimalBuildings = solver(initialBuildings);
}

