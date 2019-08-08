export function generate() {
  return new Float32Array(
    [0, 20, 40].flatMap(offset => [
      0,
      offset,
      10,
      offset,
      10,
      10 + offset,
      0,
      10 + offset,
      10
    ])
  );
}
