# WebAssembly course

In this course you will get an introduction to WebAssembly and 3D visualization using Three.js.

WebAssembly is a binary compilation format which lets you run languages like C, C++ and Rust in the browser.
This means exising code can be used in web application and possibilies for increased performance by using lower-level languages than JavaScript.
Three.js is a highly successful library which is used to create 3D applications which run in the browser.

At Spacemaker we use Three.js in large parts of our applications to let our users interact buildings on
building sites, and to visualize analysis of the buildings. WebAssembly is an emerging technology
which we have done some experiments with and are considering to include in our product.

In the first part of the course we will give you an introduction to WebAssembly and Three.js, and in the
the second part you will finish a project which combines both these technologies to find an optimal
utilization of a building site. (no prior knowledge about WebAssembly, Three.js or optimization is required.)

## Usage

Install dependencies with `npm install` and [`emcc`](https://emscripten.org/docs/getting_started/downloads.html)

Build the code with `./build.sh`

Start a web server `npm run start`

Open your browser on `http://localhost:3000`

## Assignment

The assignments in this workshop have 2 parts. First you will finish the
missing parts of code. You can find these by searching through the code by
number, e.g. "1." for the first task. When you finish one task you should be
able to refresh your browser and see a visual change. When you have completed
all 9 tasks you should have a complete program which searches and visualizes
the iterations until an optimal solution is found.

The second part builds on the foundation in part 1 with more advanced tasks.
Here we have put together independent tasks so that you can choose the task
you would like to try based on what interests you.

### 1. Rendering the scene

At the center of all 3D application is the `render` call. It tells your CPU
to update the scene and geometry on the GPU, and to schedule a rendering pass.
This will result in a 3D image being written to the framebuffer of the GPU.
This framebuffer will be mapped to the screen.

### 2. Implementing the render loop

The render method must be called each time we want to update the image on
the screen. This is usually done in a render loop running at 60 frames per
second. This means that the render function will be called every ~16 ms
and can't more time to finish. If it takes more time, we will get
less that 60 fps, which might result in noticable lagg.

The browser has a function called `requestAnimationFrame`. This function
is intended to be used for animations. Using it will ensure that our
render loop runs at the same frequency as our monitor, which is usually
60 fps.

### 3. Building the scene

A `Three.js` object consists of two main properties. The `geometry`
describes the location and shape of the object, while the `material`
describes how it looks. There is more than one way of building these
objects. In this task we will use a `THREE.Shape` which defines
a 2d shape on a plane. And a `THREE.ExtrudeGeometry` to extend the shape
with a height. This cooresponds to a building with an uniform height (flat roof) and vertical
walls.

The data model for our houses is a 2d ground polygon plus the height
of the building. These are flattened into a list of numbers
(`[x0, y0, x1, y1, x2, y2, x3, y3, height, ... ]`). The first building
is at indexes 0-8 in the array, the second at 9-16 and so on.

### 4. Adding a directional light

The light source in the scene is an Ambient light. This will uniformly
light every object in the scene. It is a convenient light to add to emulate
real light conditions and enhance shadows. However, real lighting situations
have a source of the light. We will add a Directional Light source to emulate
sun light, which is a source far away from our scene.

We want our Directional Light to cast shadows. This takes a bit of code to
set up for nice results. The gist is that the GPU creates the light source
by placing an Orthograpic Camera at the position of the light source and takes
a picture of the scene. Every thing that it sees is deemed to receive light
and the rest is shadow. This technique is called shadow mapping.
The parameters we set on `light.shadow.camera` is the size of this camera.

In addition to configuring the light source we need to set `receiveShadow`
and `castShadow` to `true` on each object which should receive and cast
shadows respectively.

### 5. Loading a WebAssembly module

To compile C++ to WebAssembly and to load it into the browser we will use
the `emscripten` toolchain. This does a lot of the heavy lifting on our behalf
by both loading and wrapping the wasm module with a JavaScript wrapper.

Lets first look at a much simpler example so that we can load and wrap the wasm
module our selves.

To compile the module run the following command in your commandline.

```bash
emcc -Os -s EXPORTED_FUNCTIONS='["_move"]' src/simple/simple.c -o src/simple/simple.wasm
```

This will create the module [`.wasm`](src/simple/simple.wasm).

Now open the [`simple.js`](src/simple/simple.js) and complete the task number 5.

Note 1: We have included the [`simple.wast`](src/simple/simple.wast) file which is the text
representation of the `.wasm` module. It was created with [`wasm2wat`](https://github.com/WebAssembly/wabt).

Note 2:

```bash
emcc                                \ # emscripten binary
  -Os                               \ # optimize for size,
                                      # (will remove all the unused code)
  -s EXPORTED_FUNCTIONS='["_move"]' \ # list of functions to keep
  src/simple/simple.c               \ # source file
  -o src/simple/simple.wasm           # output file
```

### 6. Compile and run the wasm module

Now lets build build the base implementation of the solver and call it.

Run the [`build.sh`](build.sh) script. This will create `solver.wasm` (the WebAssembly binary),
`solver.js` (Javascript wrapper) in the [`out`](out) folder.

Finish the tasks to load the module and call it.

The js wrapper generated by `emcc` exposes a method called `cwrap`.
We can use this method to generate a javascript wrapper of the
function the WebAssembly module exposes.

The signature for the `cwrap` function is as follows:

```
cwrap(ident, returnType, argTypes[, opts]);
```

#### Arguments:

- `ident` – The name of the C function to be called.
- `returnType` – The return type of the function. This can be "number", "string" or "array", which correspond to the appropriate JavaScript types (use "number" for any C pointer, and "array" for JavaScript arrays and typed arrays; note that arrays are 8-bit), or for a void function it can be null (note: the JavaScript null value, not a string containing the word “null”).
- `argTypes` – An array of the types of arguments for the function (if there are no arguments, this can be omitted). Types are as in returnType, except that array is not supported as there is no way for us to know the length of the array).
- `opts` – An optional options object, see [`ccall()`](https://emscripten.org/docs/api_reference/preamble.js.html#ccall).

#### Returns:

- A JavaScript function that can be used for running the C function.

### 7. Debugging the module in the browser

Hack need to run `ln -s ../src src` from the [`out`](out) directory.

The [`Firefox Developer Edition`](https://www.mozilla.org/nb-NO/firefox/developer/)
lets us debug the WebAssembly with source maps directly in our browser.

Open your application in `Firefox` and open the [`Developer Console`](https://developer.mozilla.org/en-US/docs/Tools/Web_Console/Opening_the_Web_Console).

You should now be able to open your `.wasm` file using the file tree or ctrl-P or cmd-P. If you now reload you can open the c++ files and set breakpoints.



## Solver track
### 1. Adding constraints
As you can see in your browser, the buildings grow until they reach the maximum height which is set in `optimize.cpp`. In most building projects, this is not the case, usually there is a limitation on the average height of the buildings. The maximum average height is often lower than the max height of each building, and that's when we need to explore the trade off space. Try implementing such a constraint by extending the method `solutionIsFeasible` in `feasibilityChecker.cpp`. Right now this returns `true` without checking anything. We have started on the function signature for a helper method for you, `getAverageHeight`.    

### 2. New objective
Right now the buildings are optimized for maximum volume, which is not so exciting. A common requirement for building projects is that the residents have a short distance to public transport. We will try to simulate this by adding a bus stop to our site and trying to move the buildings mass distribution close to this point.
The bus stop location (`BUS_STOP_COORDINATE`) is defined in `optimize.cpp`. 

In the main function in `main.cpp`, you can set what you want your objective to be, currently it is set to `VOLUME`, but you can change it to `BUS_STOP_DISTANCE`. The solver evaluates the solutions through a cost function, the cost function `getCost` is defined in `cost.cpp`. Here you can see that it computes the cost based on which objective is set. Currently the `getDistanceToBusStopCost` is empty. Try implementing it.

Hint 1: The function `getCentroid` in `geometry.cpp` can be useful
Hint 2: Remember that we want as many people (volume) as possible to be close to the bus stop. 
Hint 3: Shorter distance should give higher cost
 