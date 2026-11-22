#include "versus_globals.h"

#define INITIALIZE(Entry, Out, A, B, V1, V2, V3, V4) \
    void __cdecl Entry(void) \
    { \
        Out[0] = B * A; \
        Out[1] = V1; \
        Out[2] = V2; \
        Out[3] = V3; \
        Out[4] = V4; \
    }

INITIALIZE(initialize_2d85c0, defaults_374698, factor_2ff1d4, factor_310a10, 5.0f, 3.0f, 5.0f, 10.0f)
INITIALIZE(initialize_2d9c50, defaults_374674, factor_2ff1b0, factor_310a10, 5.0f, 3.0f, 5.0f, 10.0f)
INITIALIZE(initialize_2dae70, defaults_374650, factor_2ff198, factor_310a10, 5.0f, 3.0f, 5.0f, 10.0f)
INITIALIZE(initialize_2daed0, defaults_37462c, factor_2ff18c, factor_310a10, 5.0f, 3.0f, 5.0f, 10.0f)
INITIALIZE(initialize_2daf10, defaults_374608, factor_2ff188, factor_310a10, 5.0f, 3.0f, 5.0f, 10.0f)
INITIALIZE(initialize_2daf50, defaults_3745e4, factor_2ff170, factor_310a10, 5.0f, 3.0f, 5.0f, 10.0f)
INITIALIZE(initialize_2daf90, defaults_3745c0, factor_2ff168, factor_310a10, 5.0f, 3.0f, 5.0f, 10.0f)
INITIALIZE(initialize_2dafd0, defaults_37459c, factor_2ff144, factor_310a10, 5.0f, 3.0f, 5.0f, 10.0f)
INITIALIZE(initialize_2db010, defaults_374578, factor_2ff140, factor_310a10, 5.0f, 3.0f, 5.0f, 10.0f)
INITIALIZE(initialize_2db090, defaults_374554, factor_2ff13c, factor_310a10, 5.0f, 3.0f, 5.0f, 10.0f)
INITIALIZE(initialize_2db130, defaults_374530, factor_2ff138, factor_310a10, 5.0f, 3.0f, 5.0f, 10.0f)
