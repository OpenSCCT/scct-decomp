#include "sound_manager.h"

void __stdcall SND_fn_vUnLoadResBinarySnd(tdstBlockResourceMem *res)
{
    switch (res->eType) {
    case TYPE_SAMPLE:
    case TYPE_MULTITRACK:
        sound_release_binary_resource(res);
        break;
    }
    res->bIsLoaded = 0;
    res->eType = TYPE_INVALID;
}
