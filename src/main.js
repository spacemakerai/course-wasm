import * as THREE from "./three.js";

(async function() {
  const response = await fetch("../out/main.wasm");
  const bytes = await response.arrayBuffer();
  const module = await WebAssembly.instantiate(bytes);
  const heap = new Uint8Array(module.instance.exports.memory.buffer);

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

  var camera, scene, renderer;
  var mesh;
  init();
  // animate();
  function init() {
    try {
      console.log("init");
      camera = new THREE.PerspectiveCamera(
        70,
        window.innerWidth / window.innerHeight,
        1,
        1000
      );

      var geometry = new THREE.BufferGeometry();

      const buildings = [
        {
          coodinates: [[0, 0], [200, 0], [200, 200], [0, 200]],
          height: 200
        }
      ];

      const vertices = new Float32Array(
        buildings.flatMap(({ coodinates, height }) => {
          return coodinates.flatMap((p1, j) => {
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
        })
      );

      console.log({ vertices });

      var geometry = new THREE.BufferGeometry();
      geometry.addAttribute("position", new THREE.BufferAttribute(vertices, 3));
      var material = new THREE.MeshBasicMaterial({ color: 0xffffff });
      var mesh = new THREE.Mesh(geometry, material);

      camera.position.z = -400;
      // camera.lookAt(0, 0, 0);
      window.camera = camera;
      scene = new THREE.Scene();

      scene.add(mesh);
      renderer = new THREE.WebGLRenderer({ antialias: true });
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

  /*function animate() {
    requestAnimationFrame(animate);

    renderer.render(scene, camera);
  }*/
})();
