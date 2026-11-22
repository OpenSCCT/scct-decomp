#!/bin/sh
# Builds bindgen and checks it on the synthetic fixture in tools/bindgen/tests: a unit with two
# externals, a global and a private helper, a wrong record, a misaligned unit and two corrupt
# images. Run from the repository root.
#
# The fixture object and image are base64 text: the no-game-data check refuses COFF objects and
# binary images in git. Set BINDGEN_CL to the Visual C++ Toolkit 2003 cl.exe to check the compile
# path too; the test then compiles the fixture from its recorded build_command.
set -eu

fixtures=tools/bindgen/tests
manifest="$fixtures/pc/config/synthetic-campaign.json"
# A relative folder under local/ (ignored by git): MSVC would read a /tmp path as an option.
out="local/bindgen-test.$$"
mkdir -p "$out"
trap 'rm -rf "$out"' EXIT

case "$(basename "${CC:-cc}")" in
cl | cl.exe)
	# MSYS would rewrite the /options as paths under Git Bash; this stops it for cl only.
	MSYS_NO_PATHCONV=1 "${CC}" /nologo /std:c11 /W4 /WX /Fo"$out/" /Fe"$out/bindgen.exe" \
		tools/bindgen/bindgen.c
	bindgen="$out/bindgen.exe"
	;;
*)
	"${CC:-cc}" -std=c99 -O2 -Wall -Wextra -Werror -o "$out/bindgen" tools/bindgen/bindgen.c
	bindgen="$out/bindgen"
	;;
esac

base64 -d "$fixtures/fixtures/image.bin.b64" > "$out/image.bin"
base64 -d "$fixtures/fixtures/synthetic_unit.obj.b64" > "$out/synthetic_unit.obj"
base64 -d "$fixtures/fixtures/synthetic_vtable.obj.b64" > "$out/synthetic_vtable.obj"
base64 -d "$fixtures/fixtures/synthetic_vtable_multibase.obj.b64" > "$out/synthetic_vtable_multibase.obj"

# The fragment, and the note that the function map does not list the unlisted callee.
"$bindgen" --object "$out/synthetic_unit.obj" --image "$out/image.bin" "$manifest" synthetic-unit \
	> "$out/unit.raw" 2> "$out/unit.err.raw"
tr -d '\r' < "$out/unit.raw" > "$out/unit.json"
tr -d '\r' < "$out/unit.err.raw" > "$out/unit.err"
diff -u "$fixtures/expected/synthetic-unit.json" "$out/unit.json"
diff -u "$fixtures/expected/synthetic-unit.stderr" "$out/unit.err"

# A class vtable named by a DIR32 operand, defined by the object as a read-only COMDAT: its retail
# address is bound, and its first retail entry must point into code.
"$bindgen" --object "$out/synthetic_vtable.obj" --image "$out/image.bin" "$manifest" synthetic-vtable 	> "$out/vtable.raw" 2> /dev/null
tr -d '\r' < "$out/vtable.raw" > "$out/vtable.json"
diff -u "$fixtures/expected/synthetic-vtable.json" "$out/vtable.json"

# A base subobject's table, ??_7<class>@@6B<base>@@@, is bound the same way.
"$bindgen" --object "$out/synthetic_vtable_multibase.obj" --image "$out/image.bin" "$manifest" \
	synthetic-vtable-multibase > "$out/multibase.raw" 2> /dev/null
tr -d '\r' < "$out/multibase.raw" > "$out/multibase.json"
diff -u "$fixtures/expected/synthetic-vtable-multibase.json" "$out/multibase.json"

# The same operand, when the retail table does not begin with a code address, is refused.
rm -rf "$out/notcode" && mkdir -p "$out/notcode" && cp -r "$fixtures/pc" "$out/notcode/pc"
cp "$out/image.bin" "$out/notcode/image.bin"
printf '\0\0\0\0' | dd of="$out/notcode/image.bin" bs=1 seek=1536 conv=notrunc 2> /dev/null
sum=$(sha256sum "$out/notcode/image.bin" | cut -d' ' -f1)
sed "s/\"sha256\": \"[0-9a-f]*\"/\"sha256\": \"$sum\"/" "$fixtures/pc/config/synthetic-campaign.json" 	> "$out/notcode/pc/config/synthetic-campaign.json"
sed -i "s/^# Image SHA-256 [0-9a-f]*/# Image SHA-256 $sum/" "$out/notcode/pc/function_maps/synthetic-campaign.txt"
status=0
"$bindgen" --object "$out/synthetic_vtable.obj" --image "$out/notcode/image.bin" 	"$out/notcode/pc/config/synthetic-campaign.json" synthetic-vtable > /dev/null 2> "$out/notcode.err" || status=$?
if [ "$status" -ne 1 ] || ! grep -q "does not start with a pointer into code" "$out/notcode.err"; then
	echo "vtable without code entry: expected a refusal, got status $status" >&2
	cat "$out/notcode.err" >&2
	exit 1
fi

# --check against a record that agrees, and against one that does not (which must exit 1).
"$bindgen" --check --object "$out/synthetic_unit.obj" --image "$out/image.bin" "$manifest" \
	synthetic-unit > "$out/ok.raw" 2> /dev/null
tr -d '\r' < "$out/ok.raw" > "$out/ok.txt"
diff -u "$fixtures/expected/check-ok.txt" "$out/ok.txt"

status=0
"$bindgen" --check --object "$out/synthetic_unit.obj" --image "$out/image.bin" "$manifest" \
	synthetic-wrong > "$out/diff.raw" 2> /dev/null || status=$?
if [ "$status" -ne 1 ]; then
	echo "synthetic-wrong: expected exit status 1 from --check, got $status" >&2
	exit 1
fi
tr -d '\r' < "$out/diff.raw" > "$out/diff.txt"
diff -u "$fixtures/expected/check-diff.txt" "$out/diff.txt"

# A unit whose bytes are not the retail bytes at its offset gets no bindings.
status=0
"$bindgen" --object "$out/synthetic_unit.obj" --image "$out/image.bin" "$manifest" \
	synthetic-misaligned > /dev/null 2> "$out/bad.err" || status=$?
if [ "$status" -ne 1 ] || ! grep -q "not a byte match" "$out/bad.err"; then
	echo "synthetic-misaligned: expected a byte-match failure, got status $status" >&2
	cat "$out/bad.err" >&2
	exit 1
fi

# An image that is not the locked build is refused, whether it is short or altered.
cp "$out/image.bin" "$out/changed.bin"
printf '\377' | dd of="$out/changed.bin" bs=1 seek=1000 conv=notrunc 2> /dev/null
status=0
"$bindgen" --object "$out/synthetic_unit.obj" --image "$out/changed.bin" "$manifest" \
	synthetic-unit > /dev/null 2> "$out/changed.err" || status=$?
if [ "$status" -ne 1 ] || ! grep -q "differs from the locked build" "$out/changed.err"; then
	echo "altered image: expected the locked-build refusal, got status $status" >&2
	cat "$out/changed.err" >&2
	exit 1
fi
head -c 1000 "$out/image.bin" > "$out/short.bin"
status=0
"$bindgen" --object "$out/synthetic_unit.obj" --image "$out/short.bin" "$manifest" \
	synthetic-unit > /dev/null 2> "$out/short.err" || status=$?
if [ "$status" -ne 1 ] || ! grep -q "the manifest's image is 2048" "$out/short.err"; then
	echo "short image: expected a size refusal, got status $status" >&2
	cat "$out/short.err" >&2
	exit 1
fi

# The compile path: the fixture compiled from its recorded build_command must give the same
# fragment as the committed object.
if [ -n "${BINDGEN_CL:-}" ]; then
	"$bindgen" --cl "$BINDGEN_CL" --image "$out/image.bin" "$manifest" synthetic-unit \
		> "$out/compiled.raw" 2> /dev/null
	tr -d '\r' < "$out/compiled.raw" > "$out/compiled.json"
	diff -u "$fixtures/expected/synthetic-unit.json" "$out/compiled.json"
else
	echo "compile path not run: set BINDGEN_CL to the Toolkit 2003 cl.exe to run it." >&2
fi

echo "bindgen fixtures pass."
