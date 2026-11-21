/* sound_manager.h -- resource services of the sound manager (sndmanager.cpp) and the C
   functions that reach them (sndplay.c, sndxdtool.cpp) */
#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "sound_memory.h"
#include "sound_resource.h"
#include "sound_thread.h"

/* __FILE__ of the original translation unit. */
#define SNDMANAGER_CPP_FILE \
    "\\build\\splintercellx-pc\\patch\\SplinterCell2\\technology-group\\sound\\dare\\private" \
    "\\engine\\common\\src\\toolarch\\managers\\sndmanager.cpp"

/* The renderer is a C++ object whose methods take `this` in ECX and their arguments on the
   stack. C has no spelling for that convention: a __fastcall function with each argument
   wrapped in a structure passes them the same way. The wrappers stand in for C++ and are
   open work; only slot 25 is recovered.
   guess: the class is the sibling builds' CAudioRenderer and the pointer their static member
   SndManager::m_pRenderer. */
typedef struct CAudioRenderer CAudioRenderer;
typedef struct CAudioRendererResourceArg {
    tdstBlockResourceMem *value;
} CAudioRendererResourceArg;
typedef struct CAudioRendererFlagArg {
    int value;
} CAudioRendererFlagArg;
typedef struct CAudioRendererMethods {
    void *unk_00[25];
    void (__fastcall *unload_sample)(CAudioRenderer *self, CAudioRendererResourceArg res,
                                     CAudioRendererFlagArg full);
} CAudioRendererMethods;
struct CAudioRenderer {
    const CAudioRendererMethods *methods;
};
extern CAudioRenderer *m_pRenderer;

/* guess: SndManager::UnloadResourceSample of the sibling builds */
static __forceinline void unload_resource_sample(tdstBlockResourceMem *res, int full)
{
    CAudioRendererResourceArg res_arg = { res };
    CAudioRendererFlagArg full_arg = { full };
    EnterCriticalSectionTool_();
    MouchardThreadTool(SNDMANAGER_CPP_FILE, 3586);
    m_pRenderer->methods->unload_sample(m_pRenderer, res_arg, full_arg);
    if (full && res->uRes.stSample.owned && !res->uRes.stSample.external
        && res->uRes.stSample.sample_data) {
        SND_fn_vFreeSnd(res->uRes.stSample.sample_data);
        res->uRes.stSample.sample_data = 0;
    }
    res->uRes.stSample.sample_data = 0;
    QuitCriticalSectionTool();
}

/* guess: SndManager::UnloadResourceMultiTrack of the sibling builds */
static __forceinline void unload_resource_multitrack(tdstBlockResourceMem *res, int full)
{
    if (res->bIsLoaded && full && !res->uRes.stMultiTrack.use_external && res->uRes.stMultiTrack.data)
        SND_fn_vFreeSnd(res->uRes.stMultiTrack.data);
    res->uRes.stMultiTrack.data = 0;
    res->eType = TYPE_INVALID;
}

unsigned long __cdecl simple_channels(const tdstTypeSampleMem *sample);
unsigned long __cdecl collection_channels(const tdstTypeMultiTrackMem *multitrack);
unsigned long __cdecl locked_resource_channels(const tdstBlockResourceMem *res);
unsigned long __cdecl channel_requirement(unsigned long channels);
unsigned long __cdecl resource_requirement(const tdstBlockResourceMem *res);
void __cdecl release_sample(tdstBlockResourceMem *res, int full);
void __cdecl release_sample_collection(tdstBlockResourceMem *res, int full);
void __cdecl release_sound_resource(tdstBlockResourceMem *res);
void __cdecl sound_release_binary_backend(tdstBlockResourceMem *res);
void __cdecl decode_sample_fields(const tdstBlockResourceDisk *disk, tdstBlockResourceMem *res,
                                  unsigned long internal_base, unsigned long external_base);
int __cdecl decode_sound_sample(const tdstBlockResourceDisk *disk, tdstBlockResourceMem *res,
                                unsigned long internal_base, unsigned long external_base);

/* sndxdtool.cpp */
unsigned long __cdecl SND_fn_ulGetResourceNbChannelSxd(const tdstBlockResourceMem *res);
void __cdecl sound_release_binary_resource(tdstBlockResourceMem *res);

/* sndplay.c */
unsigned long __cdecl SND_fn_ulGetResourceNbChannel(const tdstBlockResourceMem *res);
void __stdcall SND_fn_vUnLoadResBinarySnd(tdstBlockResourceMem *res);

#endif
