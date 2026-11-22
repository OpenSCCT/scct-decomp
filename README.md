# Splinter Cell: Chaos Theory matching decompilation

[![Progress](https://bytematch.dev/OpenSCCT/scct-decomp.svg)](https://bytematch.dev/OpenSCCT/scct-decomp)

Readable C and C++ that rebuilds the original *Chaos Theory* executables byte for byte.
Each platform release is tracked per executable, so the same source can serve several
versions of the game. The [OpenSCCT hub](https://github.com/OpenSCCT/OpenSCCT) pins this
repository as `decomp/` and shows its progress on the player website.

| Platform | Executables | Guide |
| --- | --- | --- |
| PC (Steam build 252084) | Campaign and co-op, Versus | [pc/README.md](pc/README.md) · [toolchain notes](pc/TOOLCHAIN.md) |
| PlayStation 2 (PAL 1.01) | Boot, offline and online programs | [ps2/README.md](ps2/README.md) |

## Status

<!-- status:begin -->
| Build and program | Verified bytes | Candidate bytes | Measured code |
| --- | ---: | ---: | ---: |
| Steam 252084 · Campaign and co-op | 1,015,431 | 32,616 | 8,082,506 bytes |
| Steam 252084 · Versus | 477,149 | 60,174 | 2,991,392 bytes |
| PAL 1.01 · Disc boot | 0 | 0 | Unmeasured |
| PAL 1.01 · Offline program | 0 | 0 | Unmeasured |
| PAL 1.01 · Online program | 0 | 8 | Unmeasured |
<!-- status:end -->

Candidates have reproduced every byte of a complete function in a clean build. Verified
bytes additionally need reviewed evidence of the original compiler and flags. The
machine-readable feed is [reports/progress.json](reports/progress.json), and
[ByteMatch](https://bytematch.dev/OpenSCCT/scct-decomp) reads the same receipts.

### Matched under the rules

Matching bytes prove the source is faithful; readable source is the point. A unit counts as
**matched under the rules** only when its bytes match *and* its source passes every [match] rule
of the [code rules](docs/code-rules/README.md): one declaration per type and global, no offset
casts, real vtables, no fake code, no assembly bodies. A unit that reproduces the bytes with
scattered declarations or a compiler-steering trick is `MATCH-PENDING`: open work, not progress.

<!-- rules:begin -->
| Build and program | Bytes matched | Verified | Verified under the rules | `MATCH-PENDING` |
| --- | ---: | ---: | ---: | ---: |
| Steam 252084 · Campaign and co-op | 1,048,047 | 1,015,431 | 185,755 | 853,654 |
| Steam 252084 · Versus | 537,323 | 477,149 | 25,176 | 492,464 |
| PAL 1.01 · Online program | 8 | 0 | 0 | 0 |
<!-- rules:end -->

[reports/rules.json](reports/rules.json) holds the same totals with the count behind each rule;
`rules --explain <unit>` lists what holds one unit back. Nearly all pending units fail R1 or R2:
each source file declares its own copy of the types and globals it touches. The
[project profile](AGENTS.md) says how to fix that, and from which evidence names may be taken.

**PC.** Both Steam files match the sizes and SHA-1 values in depot 13571, manifest
`2604462187318687519`; the manifests also lock each file by SHA-256.
**PS2.** The PAL disc's `SYSTEM.CNF` boots `SLES_532.87`; the offline and online ELF
programs are fingerprinted separately. Each mixes code and data in one executable
section, so a reviewed code map is needed before a percentage can be measured.

## Layout

| Path | Contents |
| --- | --- |
| `<platform>/config/` | One manifest per executable: SHA-256, executable sections and matched units. Large targets keep units in 64 KiB shards under `units/`. |
| `<platform>/src/` | Independently written C and C++ sources |
| `pc/function_maps/` | Function boundaries from Ghidra analysis, as file offsets (no game bytes), so ByteMatch can draw unmatched code function by function; `pc/README.md` explains how to regenerate them |
| `tools/` | Image reader, progress tracker, x86 COFF linker, ByteMatch export, progress publisher |
| `tools/rules/` | Code-rule checker (C): computes which matched units also pass the [match] rules |
| `tools/evidence/` | Symbol indexer (C) for sibling builds that shipped with symbols |
| `docs/code-rules/` | The code rules; `AGENTS.md` at the root is this project's profile |
| `reports/progress.json` | Generated feed used by the website and ByteMatch |
| `reports/rules.json` | Generated totals of units matched under the rules |

Game files, disc images, compiled objects and analysis databases stay in an ignored
`local/` folder or outside the checkout. `tools/ci/no_game_data.py` enforces this in CI.

## How matching works

1. **Disassemble.** Verify your own executable against its manifest hash. Keep extracted
   bytes, disassembly and databases under `local/`.
   [Source and evidence rules](https://github.com/OpenSCCT/OpenSCCT/blob/main/re/PROVENANCE.md)
2. **Rewrite.** Write one complete function in the language and dialect the original used,
   following the [code rules](docs/code-rules/README.md) and the [project profile](AGENTS.md):
   shared declarations, typed members, names from evidence. Record the compiler and flags.
3. **Verify.** Link compiler-emitted references against retail evidence and compare the
   whole function. Commit the source, recipe and receipt hashes.

```text
python tools/progress.py identify PATH_TO_EXECUTABLE
python tools/progress.py verify EDITION TARGET PATH_TO_EXECUTABLE
python tools/progress.py match EDITION TARGET PATH_TO_EXECUTABLE UNIT BUILT_ARTIFACT
python tools/progress.py report [--check]
python -m unittest discover -s tools
cc -std=c99 -O2 -o local/bin/rules tools/rules/rules.c
local/bin/rules [--findings] [--explain UNIT] [--json reports/rules.json] [--check]
```

## Reading a report

The numerator counts nonoverlapping whole units with a recorded byte-for-byte comparison
**and** reviewed original build evidence (`recipe_evidence`: compiler, flags and a
Markdown basis). When the original compiler build cannot optimise or is unavailable, the
evidence names it as `original_compiler` and the basis must show that the compiler used
generates the same code ([Campaign basis](pc/evidence/campaign-vc71-o2.md), [Versus basis](pc/evidence/versus-vc71-o2.md)).
Byte-identical candidates are counted separately until that evidence exists.
Each receipt binds the original build hash, unit boundaries, compiler recipe and
tracked inputs to the result; CI checks receipts against their inputs with synthetic
fixtures.

For the PC images the denominator is the file-backed part of executable code sections,
excluding writable sections and file-alignment padding. A mixed code/data ELF stays
unmeasured until a reviewed `code_map` lists its code ranges. The feed uses `null` for
an unknown denominator.

## Publishing progress

After committing a new report, update a running Linux master from this checkout (the SSH
user needs passwordless sudo):

```powershell
python tools/publish_progress.py ubuntu@master.lumbridge.co.uk --key "$HOME/.ssh/lightsail-eu-west-2.pem"
```

It runs `report --check`, confirms the report matches `HEAD`, and installs those bytes
atomically, refusing a report outside this checkout's history or a concurrent change.
Use `--data-directory` for a custom `Master.DataDirectory`.

## Tools

[Ghidra](https://github.com/NationalSecurityAgency/ghidra) for x86 and MIPS analysis ·
[objdiff](https://github.com/encounter/objdiff) for instruction diffs ·
[splat](https://github.com/ethteck/splat), [spimdisasm](https://github.com/Decompollaborate/spimdisasm)
and [m2c](https://github.com/matt-kempster/m2c) for PS2 ·
[decomp.me](https://decomp.me/) for shared compiler experiments ·
[PCSX2](https://pcsx2.net/) for runtime comparison.
The hub's [Ghidra and UnrealScript tools](https://github.com/OpenSCCT/OpenSCCT/blob/main/re/README.md)
and [behaviour specs](https://github.com/OpenSCCT/OpenSCCT/blob/main/spec/README.md) help identify functions.

Conventions follow OpenRAC's per-game decompilation repositories, for example
[rac1-decomp](https://github.com/OpenRAC/rac1-decomp/blob/main/CONTRIBUTING.md).
