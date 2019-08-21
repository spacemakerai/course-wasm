// 5. Import the `Solver` wrapper from `./solver/solver.js`
import { generate } from "./generate.js";
import * as Visualize from "./visualize/visualize.js";

const site = generate();

Visualize.init(site);

// 5. Add a call to the `Solver.init` method
// This has the same interface as the `SimpleSolver`
// Call the `solver.iterate()` function in
// a call to the javascript `setInverval` method.
// This will run multiple iterations of the solver
// The `solver.iterate` returns true when the solution
// has conveged to a local optimum.
