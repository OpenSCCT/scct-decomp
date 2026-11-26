/* sound_error_init.c -- initializes sound error occurrence flags */
#include "sound_error.h"

#define SND_ERROR_OCCURRENCE_COUNT 44

/* Placeholder for the one-byte cdecl function called by the named export. */
void __cdecl Unk_1103c8a0(unsigned long value);

/* SND_fn_vInitErrorSnd */
void __stdcall SND_fn_vInitErrorSnd(unsigned long value)
{
    int index;

    for (index = 0; index < SND_ERROR_OCCURRENCE_COUNT; ++index)
        SND_g_astErrorOccurArray[index].bDontDisplayAnyMore = 1;

    Unk_1103c8a0(value);
}
