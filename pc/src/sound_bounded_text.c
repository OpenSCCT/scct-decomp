/* sound_bounded_text.c -- bounded string copy and concatenation (sndstr.c) */
#include "sound_error.h"
#include "sound_string.h"

/* SND_fn_vStrncpy: size counts the terminator; a longer source is cut and reported */
void __stdcall SND_fn_vStrncpy(char *dest, const char *src, unsigned int size)
{
    int truncated = 0;
    if (size > 0) {
        if (strlen(src) + 1 > size) {
            truncated = 1;
            SND_fn_vDisplayErrorEx(E_uwSndGenericWarning,
                                   "Could not copy entirely source into destination string.", 3);
        }
        strncpy(dest, src, size);
        if (truncated)
            dest[size - 1] = 0;
    }
}

/* SND_fn_vStrncat: size counts the terminator; a longer result is cut and reported */
void __stdcall SND_fn_vStrncat(char *dest, const char *src, unsigned int size)
{
    if (size > 0 && size > strlen(dest) + 1) {
        if (strlen(dest) + strlen(src) + 1 > size)
            SND_fn_vDisplayErrorEx(E_uwSndGenericWarning,
                                   "Could not copy entirely source into destination string.", 3);
        strncat(dest, src, size - strlen(dest) - 1);
    }
}
