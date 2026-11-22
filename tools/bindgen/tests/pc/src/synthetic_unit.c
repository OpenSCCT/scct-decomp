/* synthetic_unit.c -- fixture for tools/bindgen. Invented for the test: it calls two external
   functions, reads one external global and calls a static helper of its own object. It is not
   game code, and its bytes exist only as the fixture object and fixture image. */

#include "synthetic_types.h"

extern int ext_callee(int value);
extern int ext_unlisted(int value);
extern int ext_global;

/* Keeps the helper out of line, so the unit calls it as a private function of its object. */
#pragma inline_depth(0)
static int helper(int value)
{
    int total = 0;
    int i;
    for (i = 0; i < value; i++)
        total += i * SYNTHETIC_SCALE;
    return total;
}

int unit_function(int value)
{
    return ext_callee(value) + ext_unlisted(value) + ext_global + helper(value);
}
