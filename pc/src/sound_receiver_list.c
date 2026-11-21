/* sound_receiver_list.c -- the list of microphones (sndxdmic.c) */
#include "sound_memory.h"
#include "sound_micro.h"

/* reset_sound_receivers: empties the microphone list.
   guess: SND_fn_eInitSxdMic of the sibling builds, which takes the library's init structure */
int __cdecl reset_sound_receivers(const void *unused)
{
    g_iNbMicrosSxd = 0;
    gs_stMicrosSxd.pList.hFirstElementDyn = 0;
    gs_stMicrosSxd.pList.hLastElementDyn = 0;
    gs_stMicrosSxd.pList.lNumberOfElementsDyn = 0;
    return 1;
}

/* Copies the four vectors of a microphone's parameters into its description. */
static __forceinline void copy_micro_param(tdstMicroDescription *pstMicro, const MicroParam *par)
{
    SND_fn_vMemCopySnd(&pstMicro->pos, &par->pos, sizeof(SndVector));
    SND_fn_vMemCopySnd(&pstMicro->vit, &par->vit, sizeof(SndVector));
    SND_fn_vMemCopySnd(&pstMicro->dir_nor, &par->dirnor, sizeof(SndVector));
    SND_fn_vMemCopySnd(&pstMicro->dir_tan, &par->dirtan, sizeof(SndVector));
}

/* create_sound_receiver: adds a microphone at the end of the list and returns its description.
   guess: SND_fn_lCreateMicroSxdMic of the sibling builds */
tdstMicroDescription *__cdecl create_sound_receiver(const MicroParam *par)
{
    tdstMicroDescription *pstMicro = SND_fn_pvMallocSnd(sizeof(tdstMicroDescription));
    pstMicro->hPrevBrotherDyn = 0;
    pstMicro->hFatherDyn = 0;
    pstMicro->hNextBrotherDyn = 0;
    pstMicro->hPrevBrotherDyn = gs_stMicrosSxd.pList.hLastElementDyn;
    pstMicro->hFatherDyn = &gs_stMicrosSxd.pList;
    if (!gs_stMicrosSxd.pList.hFirstElementDyn)
        gs_stMicrosSxd.pList.hFirstElementDyn = pstMicro;
    else
        gs_stMicrosSxd.pList.hLastElementDyn->hNextBrotherDyn = pstMicro;
    gs_stMicrosSxd.pList.hLastElementDyn = pstMicro;
    ++gs_stMicrosSxd.pList.lNumberOfElementsDyn;
    if (!par) {
        ++g_iNbMicrosSxd;
        pstMicro->bJustCreated = 1;
    } else {
        copy_micro_param(pstMicro, par);
        ++g_iNbMicrosSxd;
    }
    return pstMicro;
}

/* update_sound_receiver: sets the parameters of a microphone that is in the list.
   guess: SND_fn_vSetMicroParamSxdMic of the sibling builds */
void __cdecl update_sound_receiver(tdstMicroDescription *sxdId, const MicroParam *par)
{
    tdstMicroDescription *pstMicro;
    for (pstMicro = gs_stMicrosSxd.pList.hFirstElementDyn; pstMicro; pstMicro = pstMicro->hNextBrotherDyn)
        if (pstMicro == sxdId)
            break;
    if (pstMicro) {
        pstMicro->bJustCreated = 0;
        copy_micro_param(pstMicro, par);
    }
}

/* destroy_sound_receiver: takes a microphone out of its list and frees it.
   guess: SND_fn_vDestroyMicroSxdMic of the sibling builds */
void __cdecl destroy_sound_receiver(tdstMicroDescription *pstMicro)
{
    if (!pstMicro)
        return;
    if (pstMicro->hNextBrotherDyn)
        pstMicro->hNextBrotherDyn->hPrevBrotherDyn = pstMicro->hPrevBrotherDyn;
    if (pstMicro->hPrevBrotherDyn)
        pstMicro->hPrevBrotherDyn->hNextBrotherDyn = pstMicro->hNextBrotherDyn;
    if (pstMicro->hFatherDyn) {
        --pstMicro->hFatherDyn->lNumberOfElementsDyn;
        if (pstMicro->hFatherDyn->hFirstElementDyn == pstMicro)
            pstMicro->hFatherDyn->hFirstElementDyn = pstMicro->hNextBrotherDyn;
        if (pstMicro->hFatherDyn->hLastElementDyn == pstMicro)
            pstMicro->hFatherDyn->hLastElementDyn = pstMicro->hPrevBrotherDyn;
    }
    pstMicro->hNextBrotherDyn = 0;
    pstMicro->hPrevBrotherDyn = 0;
    pstMicro->hFatherDyn = 0;
    SND_fn_vFreeSnd(pstMicro);
    --g_iNbMicrosSxd;
}
