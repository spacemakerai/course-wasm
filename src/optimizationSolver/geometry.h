//
// Created by Kristine Hagen on 2019-08-05.
//

#ifndef COURSE_WASM_GEOMETRY_H
#define COURSE_WASM_GEOMETRY_H
#include <vector>


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

double simpleArea(Building building);
double getHeight(Building building);

#endif //COURSE_WASM_GEOMETRY_H
