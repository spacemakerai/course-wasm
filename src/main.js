import * as Solver from "./solver/solver.js";
import * as SimpleSolver from "./simple/simple.js";
import { generate } from "./generate.js";
import * as Visualize from "./visualize/visualize.js";

const site = generate();

Visualize.init(site);
SimpleSolver.init(site).then(solver => {setInterval(solver.iterate, 1000);
});




