import * as THREE from "../three.js";
import {createCustomMaterial} from "./shaderMesh.js"

function chunk(array, chunkSize) {
  const result = [];
  for (let i = 0; i < array.length; i += chunkSize)
    result.push(array.slice(i, i + chunkSize));
  return result;
}

const createBuilding = (coordinates, height, bus_stop_position) => {
  const [[x0, y0], [x1, y1], [x2, y2], [x3, y3]] = coordinates;

  const shape = new THREE.Shape();
  // 3. Build the 2d ground polygon.
  // The `THREE.Shape` object has a `moveTo(x, y)` and `lineTo(x, y)` method.
  // Think of this as if you where drawing on paper.
  // `moveTo` moves your pencil without touching the paper
  // `lineTo` will a staight line from your current position to the new point
  shape.moveTo(x0, y0);
  shape.lineTo(x1, y1);
  shape.lineTo(x2, y2);
  shape.lineTo(x3, y3);
  shape.lineTo(x0, y0);

  const geometry = new THREE.ExtrudeGeometry(shape, {
    depth: height,
    bevelEnabled: false
  });

  const material = createCustomMaterial(geometry, bus_stop_position)

  // const material = new THREE.MeshLambertMaterial({
  //   color: 0xfafafa
  // });

  const building = new THREE.Mesh(geometry, material);
  // 4. The `THREE.Mesh` must have `receiceShadow` and `castShadow` set to true
  building.receiveShadow = true;
  building.castShadow = true;

  return building;
};

function createBuildings(buildings, bus_stop_position) {
  return chunk(buildings, 9).map(([x0, y0, x1, y1, x2, y2, x3, y3, height]) => {
    return createBuilding([[x0, y0], [x1, y1], [x2, y2], [x3, y3]], height, bus_stop_position);
  });
}

export function create(buildings, bus_stop_position) {
  const group = new THREE.Group();
  group.add(...createBuildings(buildings, bus_stop_position));
  return group;
}

export function move(group, buildings, bus_stop_position) {
  group.children = [];
  group.add(...createBuildings(buildings, bus_stop_position));
}
