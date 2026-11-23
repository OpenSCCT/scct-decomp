// campaign_crt_sqrt.h -- sqrt from the static C runtime, which the compiler expands inline as the
// x87 instruction fsqrt under /O2.
#ifndef CAMPAIGN_CRT_SQRT_H
#define CAMPAIGN_CRT_SQRT_H

extern "C" double sqrt(double);
#pragma intrinsic(sqrt)

#endif
