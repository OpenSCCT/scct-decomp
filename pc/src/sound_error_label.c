/* sound_error_label.c -- the message that names an error number (snderr.c) */
#include "sound_error.h"

/* sound_error_label */
const char *__cdecl sound_error_label(int number)
{
    int index = 0;
    unsigned short current = SOUND_ERRORS[0].number;
    while (current != number && current != 0xffff) {
        ++index;
        current = SOUND_ERRORS[index].number;
    }
    return SOUND_ERRORS[index].number == 0xffff ? "Unknown error" : SOUND_ERRORS[index].label;
}
