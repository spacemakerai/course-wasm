import * as Optimizer from "./optimizer/optimizer.js";
import { generate } from "./generate.js";
import * as Visualize from "./visualize/visualize.js";

let buildings = generate();
const render = Visualize.init(buildings);
Optimizer.init(buildings).then(render);
