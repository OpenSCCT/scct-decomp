# bindgen: a unit's inputs and link_bindings from its object

For one unit record of a Campaign target manifest, `bindgen` derives the record's `inputs` and
`link_bindings`, so matching lanes stop writing them by hand.

It reads the unit's source and the headers it reaches, compiles the source with the record's
`build_command` and toolchain, and walks the relocations of the record's function. An external's
VA comes from the retail image: the operand at the same bytes of the retail function holds the
address the call or load uses, so no symbol name is needed. A call target must be a function
entry in `pc/function_maps/<target>.txt`, and every byte outside a relocation field must equal the
retail byte, or the unit gets no bindings. With `--check` it also reports where a name's address
suffix (`_tag_7b78d8`) disagrees with the retail operand; the name is a label, never the source.

## Build

One C file, standard library only. Windows, MSVC 19.44, from a Developer Command Prompt or after
`vcvars32.bat`:

```powershell
if not exist local\bin mkdir local\bin
cl /nologo /std:c11 /W4 /WX /Fo:local\bin\ /Fe:local\bin\bindgen.exe tools\bindgen\bindgen.c
```

Other C99 compilers: `cc -std=c99 -O2 -Wall -Wextra -o local/bin/bindgen tools/bindgen/bindgen.c`.
The POSIX build is not run here, because this machine has no `cc`.

## Run

```powershell
$game = 'D:\Games\Steam Games\steamapps\common\Splintercell Chaos Theory'
$cl = 'C:\Program Files (x86)\Microsoft Visual C++ Toolkit 2003\bin\cl.exe'
local\bin\bindgen.exe --check --game $game --cl $cl pc\config\steam-252084-campaign.json band2-counter-5c-increment
```

Without `--check` it prints the record fragment `{ "id", "inputs", "link_bindings" }`. Use
`--image FILE` instead of `--game` to read a retail image elsewhere, and `--object FILE` instead of
`--cl` to use an object already built from the recorded command. The compiler runs in
`local/bindgen-build/<unit id>/`, which git ignores, and its log is kept there as `cl.log`.

`--check` lists each difference from the record and exits 1 when there is one. Notes do not count:
the inputs listed in a different order, and a name whose address suffix differs from its retail
target. A call target the function map omits is reported on standard error only.

## Tests

From a Developer Command Prompt (after `vcvars32.bat`), run the script with `cl` as the compiler and
the Toolkit 2003 `cl.exe` for the compile path:

```powershell
$env:CC = 'cl'
$env:BINDGEN_CL = 'C:\Program Files (x86)\Microsoft Visual C++ Toolkit 2003\bin\cl.exe'
sh tools/bindgen/test_bindgen.sh
```

The test builds bindgen and runs it on the invented fixture in `tests/`: a unit with two external
calls, an external global and a private helper, a wrong record, a misaligned unit, an altered
image and a short one.
It needs no game data. The fixture object and image are stored as base64 text, because the
no-game-data check refuses COFF objects and binary images. With `BINDGEN_CL` set, the test also
compiles the fixture from its recorded `build_command`.

## Limits

- **Campaign layout only.** The manifest's code sections must sit at VA `0x10900000` + file offset,
  and a PE image must have that image base; any other layout is refused. Only the Campaign manifest
  has been run.
- **Microsoft C/C++ units only**, compiled with `--cl`. VC6, Clang and `ltcg_link` units need
  `--object`; `ltcg_link`, `coff_alignment` and `rebuilt_offset` records are not handled.
- **Refused, not guessed:** static data references (the verifier cannot link them), absolute
  symbols, common symbols, C++ funcinfo (`$T`) references and relocation types other than DIR32 and
  REL32. The one special case is `__except_list`, bound at VA 0 as the verifier does.
- **Function map.** A call target the map omits is a note, because the retail call still proves it
  is code. A target inside another function's body is an error.
- **Inputs.** Only quoted `#include`s that name a project file are followed, depth first, with
  every branch of conditionals counted. System headers and `-I` paths are not searched.
- **Basis text** is generated. The record's prose is not compared, and nothing is written back to
  a record: copy the fragment's `inputs` and `link_bindings` by hand, keeping the existing order
  (the verifier's recipe hash covers the stored order of `inputs`).
- One unit per run: memory is released when the process exits.
