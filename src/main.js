import * as THREE from "./three.js"

(async function () {
  const response = await fetch('../out/main.wasm')
  const bytes = await response.arrayBuffer();
  const module = await WebAssembly.instantiate(bytes);
  const heap = new Uint8Array(module.instance.exports.memory.buffer);

  function move(positions) {
    for (let i=0; i<positions.length; i++) {
      heap[i] = positions[i];
    }

    module.instance.exports.move(0, positions.length);

    const result = [];
    for (let i=0; i<positions.length; i++) {
      result.push(heap[i]);
    }
    return result;
  }

  var camera, scene, renderer;
  var mesh;
  init();
  animate(); 
  function init() {
    try {

    console.log("init")
    camera = new THREE.PerspectiveCamera( 70, window.innerWidth / window.innerHeight, 1, 1000 );
    camera.position.z = 400;
    scene = new THREE.Scene();
    var geometry = new THREE.BoxBufferGeometry( 200, 200, 200 );
    var material = new THREE.MeshBasicMaterial();
    mesh = new THREE.Mesh( geometry, material );
    scene.add( mesh );
    renderer = new THREE.WebGLRenderer( { antialias: true } );
    renderer.setPixelRatio( window.devicePixelRatio );
    renderer.setSize( window.innerWidth, window.innerHeight );
    document.getElementById("container").appendChild( renderer.domElement );
    window.addEventListener( 'resize', onWindowResize, false );
    } catch (e) {
      console.log(e)
    }
  }
  function onWindowResize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize( window.innerWidth, window.innerHeight );
  }
  function animate() {
    requestAnimationFrame( animate );

    const {x, y, z} = mesh.position;
    const positions = move([x, y, z]);

    mesh.position.x = positions[0];
    mesh.position.y = positions[1];
    mesh.position.z = positions[2];

    renderer.render( scene, camera );
  }
})()