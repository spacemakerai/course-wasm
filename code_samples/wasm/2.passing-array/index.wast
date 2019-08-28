(module
  (type (;0;) (func (param i32 i32) (result i32)))
  (import "env" "memory" (memory (;0;) 256 256))
  (func (;0;) (type 0) (param i32 i32) (result i32)
    (local i32 i32)
    local.get 1
    i32.const 0
    i32.gt_s
    if  ;; label = @1
      loop  ;; label = @2
        local.get 3
        i32.const 2
        i32.shl
        local.get 0
        i32.add
        i32.load
        local.get 2
        i32.add
        local.set 2
        local.get 3
        i32.const 1
        i32.add
        local.tee 3
        local.get 1
        i32.ne
        br_if 0 (;@2;)
      end
    end
    local.get 2)
  (export "_sum" (func 0)))
