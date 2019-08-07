//
// Created by Kristine Hagen on 2019-08-05.
//

#ifndef COURSE_WASM_GEOMETRY_H
#define COURSE_WASM_GEOMETRY_H
#include <vector>



struct Point {
    float x;
    float y;
};
typedef std::vector<Point> Polygon;
struct Building {
    float height;
    Polygon ground_polygon;
};

float simpleArea(Building building);
float getHeight(Building building);

#endif //COURSE_WASM_GEOMETRY_H
