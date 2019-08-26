export async function init(site) {
  const memory = new WebAssembly.Memory({ initial: 256, maximum: 256 });
  const importObjects = { env: { memory } };

  /*
    Note: the following function are asynchronous and returns Promises.
    For example the `fetch` method fetches a file from the server and 
    downloads it. We need to wait for the results to return. 

    This can be done with `const response = await fetch(...);` 
  */

  // Task WASM. Loading a WebAssembly module
  // - call the `fetch` method to get the `.wasm` module
  //   pass it the path "src/simple/simple.wasm"
  //
  // - the response needs to be converted to a byte buffer
  //   you can do it with the method `.arrayBuffer()`
  //
  // - Now we create an instance of the module with `WebAssembly.instantiate`.
  //   pass it the `bytes` from the response and the `importObjects`.

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
