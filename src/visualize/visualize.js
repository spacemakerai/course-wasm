import * as THREE from "../three.js";
import * as buffered from "./buffered.js";
import * as box from "./box.js";

const geometry = buffered;

export function init(buildings, Optimizer) {
  const renderer = createRenderer();
  const camera = createCamera();

  const controls = new THREE.OrbitControls(camera, renderer.domElement);
  controls.update();

  const scene = new THREE.Scene();

  scene.add(createLight());
  scene.add(createPlane());

  const objects = geometry.create(buildings);
  scene.add(objects);

  document.getElementById("container").appendChild(renderer.domElement);
  window.addEventListener("resize", onWindowResize, false);

  return function render() {
    const start = performance.now();
    requestAnimationFrame(render);
    controls.update();

    buildings = Optimizer.move(buildings);
    geometry.move(objects, buildings);

    renderer.render(scene, camera);
    const end = performance.now();
    // console.log(end - start);
  };
}

function createRenderer() {
  const renderer = new THREE.WebGLRenderer({ antialias: true });
  renderer.shadowMap.enabled = true;
  renderer.shadowMap.type = THREE.PCFShadowMap;
  renderer.setPixelRatio(window.devicePixelRatio);
  renderer.setSize(window.innerWidth, window.innerHeight);
  return renderer;
}

function createCamera() {
  const camera = new THREE.PerspectiveCamera(
    70,
    window.innerWidth / window.innerHeight,
    1,
    1000
  );

  camera.lookAt(new THREE.Vector3(0, 0, 0));
  camera.position.x = 20;
  camera.position.z = 20;
  camera.up = new THREE.Vector3(0, 0, 1);

  return camera;
}

function createLight() {
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
  const group = new THREE.Group();
  group.add(light);
  group.add(ambient);
  return group;
}

function createPlane() {
  var geometry = new THREE.PlaneGeometry(200, 200, 32);

  geometry.computeFaceNormals();
  geometry.computeVertexNormals();
  var material = new THREE.MeshLambertMaterial({
    color: 0xdddddd,
    side: THREE.DoubleSide
  });
  var plane = new THREE.Mesh(geometry, material);

  plane.receiveShadow = plane.castShadow = true;
  return plane;
}

function onWindowResize() {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth, window.innerHeight);
}
