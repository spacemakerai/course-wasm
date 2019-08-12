const request = fetch("index.wasm");

request
  .then(response => response.arrayBuffer())
  .then(WebAssembly.compile)
  .then(m => new WebAssembly.Instance(m, importObject))

  .then(instance => {
    const array = new Uint32Array(memory.buffer);
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;

    console.log(instance.exports._sum(0, 3));
  });
