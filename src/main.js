import * as OptimizerSolver from "./solver/solver.js";
// 5. Import the simple module at ./simple/simple.js
import * as Simple from "./simple/simple.js";
import { generate } from "./generate.js";
import * as Visualize from "./visualize/visualize.js";

const site = generate();

Visualize.init(site);

OptimizerSolver.init(site).then(solver => {
  const id = setInterval(() => {
    if (solver.iterate()) {
      clearInterval(id);
    } else {
    }
  }, 100);
});

// 5. Call the `init` method for the Simple module
// The method returns a promise which resolves to
// a object with an iterate method. Calling this
// method will call the WebAssembly module
/*
Simple.init(site).then(simple => simple.iterate());
*/
