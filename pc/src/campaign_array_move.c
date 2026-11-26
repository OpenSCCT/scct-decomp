// campaign_array_move.c -- shared byte-range move wrapper for Campaign arrays.

#include <string.h>

void *__cdecl array_move(void *to, const void *from, unsigned size)
{
    return memmove(to, from, size);
}
