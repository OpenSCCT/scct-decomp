# C++ unwind sections

This note is the `recipe_evidence` basis for units whose `rebuilt_symbol` is a
frame handler label, `__ehhandler$<function>`. Each such unit is the unwind
section of one C++ function: the code Microsoft C/C++ emits into `.text$x`
beside a function that has an exception frame.

## What the unit is

For a function with objects to destroy during unwinding, VC7.1 emits a
`.text$x` section holding:

1. one funclet per unwind action, each destroying one object (for a class
   destructor: a member, or the parent class) and jumping to its destructor;
2. the frame handler stub, `mov eax, FuncInfo; jmp __CxxFrameHandler`, whose
   address the function itself pushes when it builds its exception frame.

The unit links that whole section, from the first funclet to the end of the
stub. The FuncInfo label (`$T…` in `.xdata$x`) and `__CxxFrameHandler` are
bound to their retail addresses. The audit then checks, from retail alone:

- the stub loads the bound FuncInfo and jumps to an import thunk for
  `__CxxFrameHandler`;
- the FuncInfo has magic `0x19930520`, no try blocks, and an unwind map whose
  actions start exactly at the unit's funclets, the first at the unit's start;
- every indexed function inside the range starts at one of those funclets or
  at the stub;
- each funclet ends in a jump or return, and its targets are indexed functions
  or single-jump thunks to them.

Identical unwind sections are folded by the linker, so one retail section can
serve several functions. Each retail section is one unit, rebuilt from any
function whose section links byte-identical to it.

## Compiler and switches

The section is compiled in the same translation unit, in the same compiler
run, as its function. A unit's compiler, original compiler and switches are
therefore those of the matched function it was rebuilt from, which carries its
own evidence ([Campaign](campaign-vc71-o2.md), [Versus](versus-vc71-o2.md)).
A unit is given evidence only when that function has it.
