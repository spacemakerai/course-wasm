

typedef struct __attribute__((__packed__))
{
  float x, y;
} Coordinate;

typedef struct __attribute__((__packed__))
{
  float x1, y1, x2, y2, x3, y3, x4, y4;
  float height;
} Building;

WASM_EXPORT
void move(float *numbers, int n)
{
  Building *buildings = (Building *)numbers;

  buildings[0].height += 0.01;
}
