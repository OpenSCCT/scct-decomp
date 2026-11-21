#include "sound_manager.h"

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
