#!/bin/bash

emcc -Os -s EXPORTED_FUNCTIONS='["_move"]' simple.c -o simple.wasm
wasm2wat simple.wasm -o simple.wat