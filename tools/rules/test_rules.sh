#!/bin/sh
# Builds the rule checker and compares its output on the synthetic fixtures in
# tools/rules/tests with the reviewed expectation. Run from the repository root.
set -eu

out="${TMPDIR:-/tmp}/scct-rules-test.$$"
mkdir -p "$out"
trap 'rm -rf "$out"' EXIT

"${CC:-cc}" -std=c99 -O2 -Wall -Wextra -Werror -o "$out/rules" tools/rules/rules.c

{
	"$out/rules" --root tools/rules/tests --findings
	"$out/rules" --root tools/rules/tests --units "$out/units.tsv"
	cat "$out/units.tsv"
} | tr -d '\r' > "$out/actual.txt"

if ! diff -u tools/rules/tests/expected.txt "$out/actual.txt"; then
	echo "rule checker output differs from tools/rules/tests/expected.txt" >&2
	exit 1
fi
echo "Rule checker fixtures pass."
