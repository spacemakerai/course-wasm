import * as THREE from "../three.js";

export function create(buildings) {
  const vertices = createVertices(buildings);

  const geometry = new THREE.BufferGeometry();

  geometry.addAttribute(
    "position",
    new THREE.Float32BufferAttribute(vertices, 3)
  );
  geometry.verticesNeedUpdate = true;
  geometry.computeFaceNormals();
  geometry.computeVertexNormals();
  const material = new THREE.MeshLambertMaterial({
    color: 0xfafafa
  });
  const facades = new THREE.Mesh(geometry, material);

  // 4.
  // facades.receiveShadow = facades.castShadow = true;

  return facades;
}

export function move(object, buildings) {
  const positions = object.geometry.attributes.position;
  positions.array.set(createVertices(buildings));
  positions.needsUpdate = true;
}

function chunk(array, chunkSize) {
  const result = [];
  for (let i = 0; i < array.length; i += chunkSize)
    result.push(array.slice(i, i + chunkSize));
  return result;
}

function createVertices(buildings) {
  return chunk(buildings, 9).flatMap(building => {
    const [x0, y0, x1, y1, x2, y2, x3, y3, height] = building;
    const coodinates = [[x0, y0], [x1, y1], [x2, y2], [x3, y3]];

    const facades = coodinates.flatMap((p1, j) => {
      const start = 0;
      const p2 = coodinates[(j + 1) % coodinates.length];
      const corners = [
        [p1[0], p1[1], start],
        [p2[0], p2[1], start],
        [p2[0], p2[1], height],
        [p1[0], p1[1], height]
      ];
      return [
        ...corners[0],
        ...corners[1],
        ...corners[2],
        ...corners[0],
        ...corners[2],
        ...corners[3]
      ];
    });

    const roof = [
      ...[x0, y0, height],
      ...[x1, y1, height],
      ...[x2, y2, height],
      ...[x2, y2, height],
      ...[x3, y3, height],
      ...[x0, y0, height]
    ];

    return [...facades, ...roof];
  });
}
