import * as THREE from "../three.js";
import * as buffered from "./buffered.js";
import * as box from "./box.js";
import * as extrude from "./extrude.js";

const geometry = extrude;

export function init(site) {
  const renderer = createRenderer();
  const camera = createCamera();

  const controls = new THREE.OrbitControls(camera, renderer.domElement);

  const scene = new THREE.Scene();

  scene.add(createLight());
  scene.add(createPlane());

  const objects = geometry.create(site.getBuildings());
  scene.add(objects);

  document.getElementById("container").appendChild(renderer.domElement);
  window.addEventListener("resize", onWindowResize, false);

  site.onChange(buildings => geometry.move(objects, buildings));

  // 2. uncomment the follwing function to implement the render loop
  /*
  function render() {
    controls.update();

    // move the renderer.render call here

    // call the requestAnimationFrame with the render function as an argument
  }
  */

  function onWindowResize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
  }
  // 1. insert `renderer.render(scene, camera)` here

  // 2. call render() (you should remove the render call from the previous task)
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
  camera.position.x = 100;
  camera.position.z = 100;
  camera.up = new THREE.Vector3(0, 0, 1);

  return camera;
}

function createLight() {
  const group = new THREE.Group();
  const ambient = new THREE.AmbientLight(0xf0f0f0, 0.55);
  // 4. Uncomment the following code to add an Directional Light
  /*
  const light = new THREE.DirectionalLight(0xffffff, 0.45);
  light.position.set(80, 20, 20);
  light.castShadow = true;
  const size = 200;
  light.shadow.camera.near = 10;
  light.shadow.camera.far = 1000;
  light.shadow.camera.left = -size;
  light.shadow.camera.right = size;
  light.shadow.camera.top = size;
  light.shadow.camera.bottom = -size;

  group.add(light);
  */
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
