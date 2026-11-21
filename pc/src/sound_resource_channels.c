#include "sound_manager.h"

__declspec(noinline) unsigned long __cdecl simple_channels(const tdstTypeSampleMem *sample)
{
    return sample->channels;
}

__declspec(noinline) unsigned long __cdecl collection_channels(const tdstTypeMultiTrackMem *multitrack)
{
    unsigned long best = 0;
    int i;
    const tdstMultiTrackElement *elements = multitrack->hFirstElementOpt;
    for (i = 0; i < multitrack->lNumberOfElementsOpt; ++i)
        if (elements[i].channels > best)
            best = elements[i].channels;
    return best;
}

__declspec(noinline) unsigned long __cdecl locked_resource_channels(const tdstBlockResourceMem *res)
{
    unsigned long channels;
    EnterCriticalSectionTool_();
    MouchardThreadTool(SNDMANAGER_CPP_FILE, 3084);
    switch (res->eType) {
    case TYPE_SAMPLE:
        channels = simple_channels(&res->uRes.stSample);
        break;
    case TYPE_MULTITRACK:
        channels = collection_channels(&res->uRes.stMultiTrack);
        break;
    case 9:
        channels = res->uRes.stType9.channels;
        break;
    default:
        QuitCriticalSectionTool();
        return 0;
    }
    QuitCriticalSectionTool();
    return channels;
}

__declspec(noinline) unsigned long __cdecl SND_fn_ulGetResourceNbChannelSxd(const tdstBlockResourceMem *res)
{
    return locked_resource_channels(res);
}

unsigned long __cdecl SND_fn_ulGetResourceNbChannel(const tdstBlockResourceMem *res)
{
    if (!res)
        return 0;
    switch (res->eType) {
    case TYPE_SAMPLE:
    case TYPE_MULTITRACK:
    case 9:
        return SND_fn_ulGetResourceNbChannelSxd(res);
    default:
        return 0;
    }
}
