import * as Solver from "./solver/solver.js";
import { generate } from "./generate.js";
import * as Visualize from "./visualize/visualize.js";

const site = generate();

Visualize.init(site);
Solver.init(site).then(solver => {
    const id = setInterval(() => {
        if (solver.iterate()) {
            clearInterval(id);
        } else {
        }
    }, 1000);
});




