/* campaign_default_outer.c -- returns the stored fallback outer object */
#include "campaign_default_outer.h"

struct Object *__cdecl default_outer(void)
{
    return default_outer_object;
}
