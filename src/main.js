import * as OptimizerSolver from "./solver/solver.js";

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
