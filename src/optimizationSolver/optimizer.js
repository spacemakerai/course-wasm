import Module from "../../out/solver.js";
const instance = Module();

let _move = instance.cwrap("move", "void", ["number", "number"]);
let dataHeap;

let length;

export async function init(buildings) {
  await new Promise(resolve => setTimeout(resolve, 1000));
  var nDataBytes = buildings.length * buildings.BYTES_PER_ELEMENT;
  var dataPtr = instance._malloc(nDataBytes);

  dataHeap = new Float32Array(instance.HEAPF32.buffer, dataPtr, nDataBytes);
  dataHeap.set(new Float32Array(buildings));
  length = buildings.length;
}

export function move() {
  _move(dataHeap.byteOffset, length);

  return new Float32Array(dataHeap.buffer, dataHeap.byteOffset, length);
}

export function cleanUp() {
  instance._free(dataHeap.byteOffset);
}
