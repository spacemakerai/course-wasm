import * as THREE from "../three.js";

const vertexShader = `
    varying vec3 vectorBetweenBusStopAndVertex; // pass the distance vector to the fragment shader
    uniform vec3 busStopPosition; // uniform passed from the material
    
    void main() {
      vectorBetweenBusStopAndVertex = position-busStopPosition;
      vec4 modelViewPosition = modelViewMatrix * vec4(position, 1.0);
      gl_Position = projectionMatrix * modelViewPosition; 
    }
  `;

const fragmentShader = `
      varying vec3 vectorBetweenBusStopAndVertex; // interpolated from the values set for each vertex in the vertex shader

      void main() {
        float distanceBetweenBusStopAndFragment = sqrt(dot(vectorBetweenBusStopAndVertex, vectorBetweenBusStopAndVertex));
        float scaledDistance = distanceBetweenBusStopAndFragment / 300.;
        gl_FragColor = vec4(
            0.1,
            1.0 - scaledDistance, // set the green channel of the pixel color to a shading of green depending on the computed distance
            0.1,
            1.0
        );
      }
  `;

export function createCustomShaderMaterial(busStopPosition) {
    let uniforms = {};
    uniforms.busStopPosition = {
        type: "vec3",
        value: new THREE.Vector3(...busStopPosition)
    };

    return new THREE.ShaderMaterial({
        uniforms: uniforms,
        fragmentShader: fragmentShader,
        vertexShader: vertexShader
    });
}
