let module, heap;

export async function init() {
  const response = await fetch("src/optimizer/main.wasm");
  const bytes = await response.arrayBuffer();
  module = await WebAssembly.instantiate(bytes);
  heap = new Float32Array(module.instance.exports.memory.buffer);
}

export function move(positions) {
  for (let i = 0; i < positions.length; i++) {
    heap[i] = positions[i];
  }

  module.instance.exports.move(0, positions.length);

  const result = [];
  for (let i = 0; i < positions.length; i++) {
    result.push(heap[i]);
  }
  return result;
}
