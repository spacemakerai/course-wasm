(module
  (type (;0;) (func (param i32 i32)))
  (import "env" "memory" (memory (;0;) 256 256))
  (func (;0;) (type 0) (param i32 i32)
    local.get 0
    local.get 0
    f32.load offset=32
    f32.const 0x1p+0 (;=1;)
    f32.add
    f32.store offset=32)
  (export "_move" (func 0)))
