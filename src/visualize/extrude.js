import * as THREE from "../three.js";
import { createCustomShaderMaterial } from "./customShader.js";

const createBuilding = (coordinates, height) => {
  const shape = new THREE.Shape();

  const [x, y] = coordinates[0];
  shape.moveTo(x, y);
  for (let i = 1; i < coordinates.length; i++) {
    const [x, y] = coordinates[i];
    shape.lineTo(x, y);
  }
  shape.lineTo(x, y);

  const geometry = new THREE.ExtrudeGeometry(shape, {
    depth: height,
    bevelEnabled: false
  });

  const busStopPosition = [100, 100, 0];
  const material = createCustomShaderMaterial(busStopPosition);

  const building = new THREE.Mesh(geometry, material);
  building.castShadow = true;
  building.receiveShadow = true;

  return building;
};

function createBuildings(buildings) {
  const blds = [];
  for (let i = 0; i < buildings.length; i++) {
    let n = buildings[i];

    i++;

    const coordinates = [];
    for (let j = 0; j < n; j += 2, i += 2) {
      coordinates.push([buildings[i], buildings[i + 1]]);
    }

    let height = buildings[i];

    blds.push(createBuilding(coordinates, height));
  }

  return blds;
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
