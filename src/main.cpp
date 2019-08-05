#include <vector>
#define WASM_EXPORT __attribute__((visibility("default")))
#include "optimizationSolver/geometry.h"
#include "optimizationSolver/optimize.h"


WASM_EXPORT
void move(unsigned char* positions, int n) {
  for (int i=0; i<n; i+=3) {
    positions[i] += 3;
    positions[i+1] += 2;
    positions[i+2] += 1;
  }
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
    Building initialBuilding{ 0, 9, polygon };
    std::vector<Building> initialBuildings{ {initialBuilding} };
    std::vector<Building> optimalBuildings = solver(initialBuildings);
}

