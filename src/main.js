import * as THREE from "./three.js";

(async function() {
  const response = await fetch("../out/main.wasm");
  const bytes = await response.arrayBuffer();
  const module = await WebAssembly.instantiate(bytes, importObjects);
  const heap = new Float32Array(module.instance.exports.memory.buffer);

  function move(positions) {
    for (let i = 0; i < positions.length; i++) {
      heap[i] = positions[i];
    }

    module.instance.exports.move(0, positions.length);

    const result = [];
    for (let i = 0; i < positions.length; i++) {
      result.push(heap[i]);
    }
    return result;
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

  function createMesh(buildings) {
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
      color: 0xff0000
    });
    const facades = new THREE.Mesh(geometry, material);
    facades.receiveShadow = facades.castShadow = true;

    return facades;
  }

  let buildings = [0, 20, 40].flatMap(offset => [
    0,
    offset,
    10,
    offset,
    10,
    10 + offset,
    0,
    10 + offset,
    10
  ]);

  var camera, scene, renderer, controls, mesh;
  init();
  animate();
  function init() {
    try {
      camera = new THREE.PerspectiveCamera(
        70,
        window.innerWidth / window.innerHeight,
        1,
        1000
      );

      camera.lookAt(new THREE.Vector3(0, 0, 0));
      camera.position.x = 20;
      camera.up = new THREE.Vector3(0, 0, 1);

      renderer = new THREE.WebGLRenderer({ antialias: true });
      renderer.shadowMap.enabled = true;
      renderer.shadowMap.type = THREE.PCFShadowMap;
      controls = new THREE.OrbitControls(camera, renderer.domElement);
      controls.update();

      scene = new THREE.Scene();

      const ambient = new THREE.AmbientLight(0xf0f0f0, 0.55);
      var light = new THREE.DirectionalLight(0xffffff, 0.1);
      light.position.set(-20, 80, 20);
      light.castShadow = true;
      scene.add(light);
      scene.add(ambient);

      var geometry = new THREE.PlaneGeometry(200, 200, 32);

      geometry.computeFaceNormals();
      geometry.computeVertexNormals();
      var material = new THREE.MeshLambertMaterial({
        color: 0xdddddd,
        side: THREE.DoubleSide
      });
      var plane = new THREE.Mesh(geometry, material);

      plane.receiveShadow = plane.castShadow = true;
      scene.add(plane);

      mesh = createMesh(buildings);
      scene.add(mesh);
      renderer.setPixelRatio(window.devicePixelRatio);
      renderer.setSize(window.innerWidth, window.innerHeight);
      document.getElementById("container").appendChild(renderer.domElement);
      window.addEventListener("resize", onWindowResize, false);
    } catch (e) {
      console.log(e);
    }
  }
  function onWindowResize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
  }

  function animate() {
    requestAnimationFrame(animate);
    controls.update();

    buildings = move(buildings);

    const positions = mesh.geometry.attributes.position;
    positions.array.set(createVertices(buildings));
    positions.needsUpdate = true;

    renderer.render(scene, camera);
  }
})();
