#define WASM_EXPORT __attribute__((visibility("default")))

typedef struct
{
  float x, y;
} Coordinate;

typedef struct
{
  Coordinate coordinates[8]; // [x0, y0, ... x3, y3],
  float height;
} Building;

WASM_EXPORT
void move(float *numbers, int nBuildings, int iterations)
{
  Building *buildings = (Building *)numbers;

  (*buildings[0].coordinates).x += 1;
  (*buildings[1].coordinates).x += 1;
}
