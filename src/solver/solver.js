import Module from "../../out/solver.js";
const instance = Module();

let _move = instance.cwrap("move", "void", ["number", "number"]);

export async function init(site) {
  await new Promise(resolve => setTimeout(resolve, 1000));
  const buildings = site.getBuildings();
  var nDataBytes = buildings.length * buildings.BYTES_PER_ELEMENT;
  var dataPtr = instance._malloc(nDataBytes);

  const dataHeap = new Float32Array(
    instance.HEAPF32.buffer,
    dataPtr,
    nDataBytes
  );
  dataHeap.set(new Float32Array(buildings));

  function iterate() {
    const buildings = site.getBuildings();

    dataHeap.set(new Float32Array(buildings));

    _move(dataHeap.byteOffset, buildings.length);

    const newBuildings = new Float32Array(
      dataHeap.buffer,
      dataHeap.byteOffset,
      buildings.length
    );

    const hasConverged = isEqual(buildings, newBuildings);

    site.setBuildings(newBuildings);

    return hasConverged;
  }

  function cleanUp() {
    instance._free(dataHeap.byteOffset);
  }

  return { iterate };
}

function isEqual(a, b) {
  if (a.length !== b.length) {
    return false;
  }

  for (let i = 0; i < a.length; i++) {
    if (a[i] !== b[i]) {
      return false;
    }
  }

  return true;
}
