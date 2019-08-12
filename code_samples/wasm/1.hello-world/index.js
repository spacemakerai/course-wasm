const request = fetch("index.wasm");

request
  .then(response => response.arrayBuffer())
  .then(WebAssembly.compile)
  .then(m => new WebAssembly.Instance(m))
  .then(instance => {
    console.log(instance.exports.add(1, 2));
  });
