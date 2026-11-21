/* sound_release_backend.c -- unloads a resource's binary data, keeping its buffers
   (sndmanager.cpp) */
#include "sound_manager.h"

/* sound_release_binary_backend.
   guess: SndManager::UnloadResourceBinary of the sibling builds */
void __cdecl sound_release_binary_backend(tdstBlockResourceMem *res)
{
    if (res) {
        EnterCriticalSectionTool_();
        MouchardThreadTool(SNDMANAGER_CPP_FILE, 3560);
        switch (res->eType) {
        case TYPE_SAMPLE:
            unload_resource_sample(res, 0);
            break;
        case TYPE_MULTITRACK:
            unload_resource_multitrack(res, 0);
            break;
        case TYPE_SILENCE:
            res->eType = TYPE_INVALID;
            break;
        }
        QuitCriticalSectionTool();
    }
}
