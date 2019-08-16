import * as THREE from "../three.js";

function chunk(array, chunkSize) {
  const result = [];
  for (let i = 0; i < array.length; i += chunkSize)
    result.push(array.slice(i, i + chunkSize));
  return result;
}

const createBuilding = (coordinates, height) => {
  const [[x0, y0], [x1, y1], [x2, y2]] = coordinates;
  const width = Math.abs(x1 - x0);
  const depth = Math.abs(y2 - y1);

  const geometry = new THREE.BoxGeometry(1, 1, 1);
  const material = new THREE.MeshLambertMaterial({
    color: 0xfafafa
  });

  const building = new THREE.Mesh(geometry, material);
  building.receiveShadow = building.castShadow = true;
  building.scale.set(width, depth, height);

  building.position.set(x0 + width / 2, y0 + depth / 2, 0 + height / 2);

  return building;
};

export function create(buildings) {
  const blds = chunk(buildings, 9).map(
    ([x0, y0, x1, y1, x2, y2, x3, y3, height]) => {
      return createBuilding([[x0, y0], [x1, y1], [x2, y2], [x3, y3]], height);
    }
  );

  const group = new THREE.Group();
  group.add(...blds);
  return group;
}

export function move(object, buildings) {
  const blds = chunk(buildings, 9);
  for (let i = 0; i < object.children.length; i++) {
    const height = blds[i][8];

    object.children[i].scale.z = height;
    object.children[i].position.z = height / 2;
  }
}
