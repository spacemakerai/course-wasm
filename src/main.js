import * as OptimizerHello from "./optimizer/optimizer.js";
import * as OptimizerSolver from "./optimizationSolver/optimizer.js";

const Optimizer = OptimizerSolver;

import { generate } from "./generate.js";
import * as Visualize from "./visualize/visualize.js";

const buildings = generate();
const render = Visualize.init(buildings, Optimizer);
Optimizer.init(buildings).then(render);
