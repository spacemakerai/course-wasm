(module
  (func $i (import "imports" "i") (param i32))
  (func (export "foo")
    i32.const 42
    call $i))