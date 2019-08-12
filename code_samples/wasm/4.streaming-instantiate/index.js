const memory = new WebAssembly.Memory({ initial: 256, maximum: 256 });

const importObject = { env: { memory } };

WebAssembly.instantiateStreaming(fetch("index.wasm")).then(({ instance }) => {
  console.log(instance.exports.add(1, 2));
});
