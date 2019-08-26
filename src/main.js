import { generate } from "./generate.js";
import * as Visualize from "./visualize/visualize.js";

const site = generate();

Visualize.init(site);

