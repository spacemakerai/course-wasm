const { Service, project } = require("@wasm/studio-utils");

const build = async () => {
  const data = await Service.compileFile(
    project.getFile("src/main.cpp"),
    "c++",
    "wasm",
    "-g -O3"
  );
  const outWasm = project.newFile("out/main.wasm", "wasm", true);
  outWasm.setData(data);
};

build();
