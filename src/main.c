#define WASM_EXPORT __attribute__((visibility("default")))

WASM_EXPORT
void move(unsigned char* positions, int n) {
  for (int i=0; i<n; i+=3) {
    positions[i] += 3;
    positions[i+1] += 2;
    positions[i+2] += 1;
  }
}
