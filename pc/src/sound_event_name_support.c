#include "sound_name_tree.h"

void __cdecl sound_set_event_name_support(unsigned long setting)
{
    event_name_support = setting;
}

unsigned long __cdecl sound_get_event_name_support(void)
{
    return event_name_support;
}
