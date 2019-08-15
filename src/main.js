import * as SolverLib from "./solver/solver.js";

const Solver = SolverLib;

import { generate } from "./generate.js";
import * as Visualize from "./visualize/visualize.js";

const buildings = generate();
const render = Visualize.init(buildings, Solver);
Solver.init(buildings).then(render);
