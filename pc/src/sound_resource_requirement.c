/* sound_resource_requirement.c -- what a resource needs from the renderer to play
   (sndmanager.cpp) */
#include "sound_manager.h"

/* resource_requirement: the largest requirement of the resource or of its elements.
   guess: SndManager::GetNbHWVoice of the sibling builds */
unsigned long __cdecl resource_requirement(const tdstBlockResourceMem *res)
{
    unsigned long result;
    EnterCriticalSectionTool_();
    MouchardThreadTool(SNDMANAGER_CPP_FILE, 3051);
    result = 0;
    switch (res->eType) {
    case TYPE_SAMPLE:
    case TYPE_MULTITRACK:
    case 9:
        result = channel_requirement(locked_resource_channels(res));
        break;
    case 5: {
        int i;
        const tdstType5Element *element = res->uRes.stType5.elements;
        for (i = 0; i < res->uRes.stType5.count; ++i, ++element) {
            unsigned long requirement = resource_requirement(element->resource);
            if (result < requirement)
                result = requirement;
        }
        break;
    }
    default:
        QuitCriticalSectionTool();
        return 0;
    }
    QuitCriticalSectionTool();
    return result;
}
