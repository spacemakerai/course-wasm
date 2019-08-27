import * as THREE from "../three.js";

const vertexShader = `
    varying vec3 distanceVec; // pass the distance vector to the fragment shader
    uniform vec3 busStopPosition; // uniform passed from the material
    
    void main() {
      distanceVec = position-busStopPosition;
      vec4 modelViewPosition = modelViewMatrix * vec4(position, 1.0);
      gl_Position = projectionMatrix * modelViewPosition; 
    }
  `;

const fragmentShader = `
      varying vec3 distanceVec; // interpolated from the values set for each vertex in the vertex shader

      void main() {
        float distance = sqrt(dot(distanceVec, distanceVec));
        float scaledDistance = distance / 400.;
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
