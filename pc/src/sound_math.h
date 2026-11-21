/* sound_math.h -- floating-point helpers of the sound library (sndmath.c) */
#ifndef SOUND_MATH_H
#define SOUND_MATH_H

/* An angle and its tangent. Only the table's name is evidenced; the type and member names
   are invented. */
typedef struct SndTanAngle {
    float angle;                    /* in turns: 1/360 per entry */
    float tangent;
} SndTanAngle;

/* File-static in sndmath.c of the sibling builds: 0 to 90 degrees, one entry per degree. */
extern SndTanAngle gs_TanAngle[91];

float __cdecl SND_fn_fFastAtan(float tangent);

#endif
