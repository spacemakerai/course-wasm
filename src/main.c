#define WASM_EXPORT __attribute__((visibility("default")))

struct Coordinate
{
  float x, y;
};

struct Building
{
  Coordinate coordinates[8]; // [x0, y0, ... x3, y3],
  float height;
};

WASM_EXPORT
void move(float *numbers, int nBuildings)
{
  Building *buildings = (Building *)numbers;

  buildings[0]->coordinates->x;

  for (int i = 0; i < nBuildings; i += 3)
  {
    positions[i] += 3;
    positions[i + 1] += 2;
    positions[i + 2] += 1;
  }
}
