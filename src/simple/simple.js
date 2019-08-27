export async function init(site) {
  const memory = new WebAssembly.Memory({ initial: 256, maximum: 256 });
  const importObjects = { env: { memory } };

  const wasmCode = await fetch("src/simple/simple.wasm");

  const byteBuffer = await wasmCode.arrayBuffer();

  const {instance } =  await WebAssembly.instantiate(byteBuffer, importObjects);

  const heap = new Float32Array(memory.buffer);

  const buildings = site.getBuildings();
  for (let i = 0; i < buildings.length; i++) {
    heap[i] = buildings[i];
  }

  function iterate() {
    instance.exports._move(0, buildings.length);

    const result = [];
    for (let i = 0; i < buildings.length; i++) {
      result.push(heap[i]);
    }

    site.setBuildings(new Float32Array(heap.buffer, 0, buildings.length));
  }

  return { iterate };
}
