
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
typedef std::vector<Building> Buildings;
float getArea(const Building& rectangularBuilding);
float getVolume(const Building& building);
Point getCentroid(const Building& rectangularBuilding);
float lengthOfLine(Point point1, Point point2);


#endif //COURSE_WASM_GEOMETRY_H
