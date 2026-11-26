# Splinter Cell: Chaos Theory matching decompilation

[![Progress](https://bytematch.dev/OpenSCCT/scct-decomp.svg)](https://bytematch.dev/OpenSCCT/scct-decomp)

This project reconstructs the retail programs for *Splinter Cell: Chaos Theory* in C and C++.
The goal is readable source code that produces the same bytes as each retail program.
The project measures each program independently. Different game versions can use the same source code.
The [OpenSCCT hub](https://github.com/OpenSCCT/OpenSCCT) records the revision of this repository in its `decomp/` directory.
The player website shows the progress for that revision.

| Platform | Programs | Documentation |
| --- | --- | --- |
| PC (Steam build 252084) | Campaign and co-op, Versus | [PC guide](pc/README.md) · [Compiler tools](pc/TOOLCHAIN.md) |
| PlayStation 2 (PAL 1.01) | Disc boot, offline program, online program | [PlayStation 2 guide](ps2/README.md) |

## Status

A **candidate** is a complete function that produces the retail bytes in a clean build.
For a **verified** function, a reviewer has also confirmed the identity of the retail compiler and its options from build records.
The table gives a byte count for each group. [Progress report](reports/progress.json)

<!-- status:begin -->
| Build and program | Verified bytes | Candidate bytes | Measured code |
| --- | ---: | ---: | ---: |
| Steam 252084 · Campaign and co-op | 1,180,131 | 37,090 | 8,082,506 bytes |
| Steam 252084 · Versus | 477,149 | 65,829 | 2,991,392 bytes |
| PAL 1.01 · Disc boot | 0 | 0 | Unmeasured |
| PAL 1.01 · Offline program | 0 | 0 | Unmeasured |
| PAL 1.01 · Online program | 0 | 8 | Unmeasured |
<!-- status:end -->

### Matched under the rules

A function is **matched under the rules** when it produces the retail bytes and its source code passes all `[match]` rules.
For example, each type and each global variable must have one declaration.
The source code must use the correct virtual method tables.
The rules prohibit offset casts, artificial code that forces a match, and function bodies written in assembly language. [Code rules](docs/code-rules/README.md)

`MATCH-PENDING` means that the function matches the retail bytes but its source code fails one or more rules.
For example, two source files can each contain a declaration for the same type (R1) or global variable (R2).
The project profile specifies how to correct these declarations and which records to use for names. [Project profile](AGENTS.md)

<!-- rules:begin -->
| Build and program | Bytes matched | Verified | Verified under the rules | `MATCH-PENDING` |
| --- | ---: | ---: | ---: | ---: |
| Steam 252084 · Campaign and co-op | 1,217,221 | 1,180,131 | 646,144 | 551,104 |
| Steam 252084 · Versus | 542,978 | 477,149 | 97,670 | 419,085 |
| PAL 1.01 · Online program | 8 | 0 | 0 | 0 |
<!-- rules:end -->

The rules report gives the totals for each program and each rule.
To find the rule that applies to a unit, use `local/bin/rules --explain UNIT`. [Rules report](reports/rules.json)

### Retail programs

**PC.** The two Steam files have the sizes and SHA-1 hashes from depot 13571, manifest `2604462187318687519`.
The project manifest also gives the SHA-256 hash for each file.

**PlayStation 2.** The PAL disc starts `SLES_532.87` as specified in `SYSTEM.CNF`.
The project records one hash for the offline ELF program and one for the online ELF program.
The executable sections of these programs contain code and data. A reviewer must examine the code ranges before the project can calculate a percentage.

## Repository layout

| Path | Contents |
| --- | --- |
| `<platform>/config/` | One manifest for each program. It contains the SHA-256 hash, executable sections, and units. For large programs, files under `units/` group the units by 64 KiB address range. |
| `<platform>/src/` | C and C++ source code written independently for this project |
| `pc/function_maps/` | File offsets for function boundaries from Ghidra. ByteMatch uses these offsets to show individual functions that still have no matching source code. The [PC guide](pc/README.md) gives the procedure to make the maps. |
| `tools/` | Programs to read executable files, measure progress, link x86 COFF objects, export ByteMatch data, and publish reports |
| `tools/rules/` | C program that finds code rule violations in matching units |
| `tools/evidence/` | C program that indexes symbols from other builds that contain symbol information |
| `docs/code-rules/` | Code rules and examples. The [project profile](AGENTS.md) specifies the rules for this repository. |
| `reports/progress.json` | Progress report for the website. ByteMatch uses the same verification records. |
| `reports/rules.json` | Byte counts and function counts from the code rules check |

Keep game files, disc images, compiled objects, and analysis databases in the ignored `local/` directory. You can also keep these files in a directory external to the checkout.
The continuous integration (CI) system examines the repository with `tools/ci/no_game_data.py`.

## How to match a function

1. Compare the hash of your executable file with the hash in its manifest.
2. Disassemble the function. Keep the extracted bytes, disassembly, and analysis database under `local/`. [Source and evidence rules](https://github.com/OpenSCCT/OpenSCCT/blob/main/re/PROVENANCE.md)
3. Write the complete function in the language and dialect of the retail program. Use shared declarations and typed members. Select names that the project records support. [Code rules](docs/code-rules/README.md) · [Project profile](AGENTS.md)
4. Record the compiler and its options.
5. Link the references from the compiler output to the addresses from the retail executable.
6. Compare all bytes of the rebuilt function with the retail bytes.
7. Commit the source code, the build recipe, and the hashes in the verification record (the *receipt*).

### Commands

In these commands, replace each uppercase parameter with its value. Brackets identify optional arguments.

```text
python tools/progress.py identify PATH_TO_EXECUTABLE
python tools/progress.py verify EDITION TARGET PATH_TO_EXECUTABLE
python tools/progress.py match EDITION TARGET PATH_TO_EXECUTABLE UNIT BUILT_ARTIFACT
python tools/progress.py report [--check]
python -m unittest discover -s tools
```

Before you compile the code rules checker, make the `local/bin/` directory.

```text
cc -std=c99 -O2 -o local/bin/rules tools/rules/rules.c
local/bin/rules [--findings] [--explain UNIT] [--json reports/rules.json] [--check]
```

## How to read a progress report

The progress percentage is the number of verified bytes divided by the number of measured code bytes, multiplied by 100.
The report counts only complete units that have a receipt and reviewed records for the retail build.
The byte ranges for these units do not overlap.
The `recipe_evidence` record identifies the compiler, its options, and a Markdown file that explains how the reviewer identified them.

If the retail compiler is unavailable or cannot optimize the code, the build record gives its name in `original_compiler`.
The build record must show that the replacement compiler produces the same code. [Campaign compiler evidence](pc/evidence/campaign-vc71-o2.md) · [Versus compiler evidence](pc/evidence/versus-vc71-o2.md)

Each receipt records the result and identifies the retail file hash, unit boundaries, build recipe, and input files in Git.
CI compares the receipts with the input files. CI also tests the verification tools with synthetic data.

For PC programs, the total includes the bytes of executable code sections that have data in the file.
The measurement excludes writable sections and file alignment padding.
For an ELF program that contains code and data in the same section, the measurement requires a reviewed `code_map`.
The report uses `null` when the number of code bytes is unknown.

## How to publish the progress report

1. Commit the new report.
2. Make sure that the SSH account can use `sudo` without a password on the Linux master server.
3. If the server uses a different `Master.DataDirectory`, add `--data-directory` and its absolute path to the command.
4. Enter the command from this checkout.

```powershell
python tools/publish_progress.py ubuntu@master.lumbridge.co.uk --key "$HOME/.ssh/lightsail-eu-west-2.pem"
```

The publisher uses `report --check` and compares the report with the copy in `HEAD`.
It replaces the server file in one operation.
It stops if the checkout history does not contain the installed report. It also stops if the server file changes during publication.

## Tools and references

| Task | Tool or reference |
| --- | --- |
| Analyze x86 and MIPS code | [Ghidra](https://github.com/NationalSecurityAgency/ghidra) |
| Compare instructions | [objdiff](https://github.com/encounter/objdiff) |
| Analyze PlayStation 2 code | [splat](https://github.com/ethteck/splat), [spimdisasm](https://github.com/Decompollaborate/spimdisasm), [m2c](https://github.com/matt-kempster/m2c) |
| Compare compiler output with other contributors | [decomp.me](https://decomp.me/) |
| Compare program behavior on PlayStation 2 | [PCSX2](https://pcsx2.net/) |
| Identify functions | [Ghidra and UnrealScript tools](https://github.com/OpenSCCT/OpenSCCT/blob/main/re/README.md), [behavior specifications](https://github.com/OpenSCCT/OpenSCCT/blob/main/spec/README.md) |

The project follows the repository conventions that OpenRAC uses for each game. [OpenRAC example](https://github.com/OpenRAC/rac1-decomp/blob/main/CONTRIBUTING.md)
