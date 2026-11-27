# Versus container functions with default inlining

The compiler and switches for the LTCG exception recipe are established in
[the Versus compiler experiments](versus-vc70-switches.md).

The FString-array copy constructor at RVA `0xc550`, the configuration section
map insertion at `0x14ae0`, and the three FMipmap constructors at `0xf4c20`,
`0xf4ca0`, and `0xf4d10` also reproduce with the standard LTCG exception
recipe. For each comparison the source, link roots, and stubs were held fixed
and the explicit `/Ob1` was removed. All five complete retail bodies still
match, totaling 537 previously receipted bytes. The manifests record the
default-inlining build and its resolved link operands.
