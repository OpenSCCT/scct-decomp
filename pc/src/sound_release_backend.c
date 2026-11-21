#include "sound_manager.h"

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
