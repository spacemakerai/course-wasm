import * as OptimizerSolver from "./solver/optimizer.js";

const Optimizer = OptimizerSolver;

import { generate } from "./generate.js";
import * as Visualize from "./visualize/visualize.js";

const buildings = generate();
const render = Visualize.init(buildings, Optimizer);
Optimizer.init(buildings).then(render);
