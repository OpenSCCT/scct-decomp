/* sound_event_name_support.c -- whether the project carries its event names */
#include "sound_name_tree.h"

/* sound_set_event_name_support */
void __cdecl sound_set_event_name_support(unsigned long setting)
{
    event_name_support = setting;
}

/* sound_get_event_name_support */
unsigned long __cdecl sound_get_event_name_support(void)
{
    return event_name_support;
}
