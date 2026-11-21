// versus_build.h -- selects the Versus executable's variant of the shared engine declarations
//
// The two retail executables are built from two branches of the engine. Classes that both
// declare live in the unreal_*.h headers; where the branches differ, the Versus variant is
// the one under SCCT_VERSUS. Every Versus unit includes this header first.
#ifndef VERSUS_BUILD_H
#define VERSUS_BUILD_H

#define SCCT_VERSUS 1

#endif // VERSUS_BUILD_H
