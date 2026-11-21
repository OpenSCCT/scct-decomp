#include "sound_manager.h"

void __cdecl sound_release_binary_resource(tdstBlockResourceMem *res)
{
    sound_release_binary_backend(res);
}
