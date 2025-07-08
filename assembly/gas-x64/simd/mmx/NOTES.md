# MMX Instruction Set

- MMX was (or is?) performed on a specialized unit called x87 FPU.
- The `mm0-7` registers are actually alias to x87 FPU registers `st0-7`.
- The x87 FPU supports two states: FPU and multimedia state. 

    To transition into multimedia state, use MMX instructions like `paddb mm0, mm1`. Once transitioned into multimedia state, you can't use the `st0-7` registers until you finish it using `emms`, which is a short for Exit Multimedia State, which will transition to FPU state.

## Data Movement

There are two move instructions:

- `movd [mmx/reg32/mem32], [mmx/reg32/mem32]`

    This will zero the top 32 bit.

    You can also perform:

    ```asm
    movd mmx0, rax
    ```

    moving 64 bit value despite the mnemonic says double even though we're moving quad.

    A few other things to note:
    - One of the operand has to be mmx register, but not both.

- `movq [mmx/reg64/mem64], [mmx/reg64/mem64]`