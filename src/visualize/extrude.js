import * as THREE from "../three.js";
import {createCustomShaderMaterial} from "./customShader.js"

function chunk(array, chunkSize) {
  const result = [];
  for (let i = 0; i < array.length; i += chunkSize)
    result.push(array.slice(i, i + chunkSize));
  return result;
}

const createBuilding = (coordinates, height) => {
  const [[x0, y0], [x1, y1], [x2, y2], [x3, y3]] = coordinates;

  const shape = new THREE.Shape();
  const geometry = new THREE.ExtrudeGeometry(shape, {
    depth: height,
    bevelEnabled: false
  });
  const material = new THREE.MeshLambertMaterial({
    color: 0xfafafa
  });

  // THREE task 1: uncomment the lines below to use the material with the custom shaders
  // let busStopPosition = [0, 0, 0]
  // const material = createCustomShaderMaterial(busStopPosition)

  const building = new THREE.Mesh(geometry, material);
  // 4. The `THREE.Mesh` must have `receiceShadow` and `castShadow` set to true

  return building;
};

function createBuildings(buildings) {
  return chunk(buildings, 9).map(([x0, y0, x1, y1, x2, y2, x3, y3, height]) => {
    return createBuilding([[x0, y0], [x1, y1], [x2, y2], [x3, y3]], height);
  });
}

export function create(buildings) {
  const group = new THREE.Group();
  group.add(...createBuildings(buildings));
  return group;
}

export function move(group, buildings) {
  group.children = [];
  group.add(...createBuildings(buildings));
}
