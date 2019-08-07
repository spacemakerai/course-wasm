import * as THREE from "./three.js";

import { generate } from "./generate.js";
import * as buffered from "./geometry/buffered.js";
import * as box from "./geometry/box.js";

(async function() {
  const response = await fetch("../out/main.wasm");
  const bytes = await response.arrayBuffer();
  const module = await WebAssembly.instantiate(bytes);
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

  let buildings = generate();

  var camera, scene, renderer, controls, objects;
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
      const shadowMapSize = 4096;
      light.shadow.mapSize.width = shadowMapSize;
      light.shadow.mapSize.height = shadowMapSize;
      const size = 600;
      light.shadow.camera.near = -size / 2;
      light.shadow.camera.left = -size;
      light.shadow.camera.right = size;
      light.shadow.camera.top = size;
      light.shadow.camera.bottom = -size;
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

      objects = box.create(buildings);
      scene.add(objects);
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
    box.move(objects, buildings);

    renderer.render(scene, camera);
  }
})();
