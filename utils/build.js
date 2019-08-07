const { Service, project } = require("@wasm/studio-utils");

const build = async () => {
  try {
    const data = await Service.compileFile(
      project.getFile("src/main.cpp"),
      "c++",
      "wasm",
      "-g -O3"
    );
    const outWasm = project.newFile("src/optimizer/main.wasm", "wasm", true);
    outWasm.setData(data);
  } catch (e) {
    console.error(e);
  }
};

build();
