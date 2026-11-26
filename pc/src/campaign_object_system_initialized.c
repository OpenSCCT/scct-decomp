/* campaign_object_system_initialized.c -- reads the engine's readiness flag */
#include "campaign_globals.h"

int __cdecl object_system_initialized(void)
{
    return object_system_ready;
}
