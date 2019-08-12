const request = fetch("index.wasm");

const importObject = {
  imports: {
    i: function(n) {
      console.log(n);
    }
  }
};

request
  .then(response => response.arrayBuffer())
  .then(WebAssembly.compile)
  .then(m => new WebAssembly.Instance(m, importObject))
  .then(instance => {
    instance.exports.foo();
  });
