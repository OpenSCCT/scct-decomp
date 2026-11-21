/* sound_resource_forward.c -- hands a resource to the sound manager to unload (sndxdtool.cpp) */
#include "sound_manager.h"

/* sound_release_binary_resource */
void __cdecl sound_release_binary_resource(tdstBlockResourceMem *res)
{
    sound_release_binary_backend(res);
}
