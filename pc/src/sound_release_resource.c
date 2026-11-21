/* sound_release_resource.c -- unloads a resource's binary data and frees its buffers
   (sndmanager.cpp) */
#include "sound_manager.h"

/* release_sound_resource */
void __cdecl release_sound_resource(tdstBlockResourceMem *res)
{
    if (!res)
        return;
    EnterCriticalSectionTool_();
    MouchardThreadTool(SNDMANAGER_CPP_FILE, 3531);
    switch (res->eType) {
    case TYPE_SAMPLE:
        release_sample(res, 1);
        break;
    case TYPE_MULTITRACK:
        unload_resource_multitrack(res, 1);
        break;
    case TYPE_SILENCE:
        res->eType = TYPE_INVALID;
        break;
    }
    QuitCriticalSectionTool();
}
