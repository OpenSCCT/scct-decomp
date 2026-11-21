/* sound_bank_records.c -- resources and events of the bank in use by index (sndldbnk.c) */
#include "sound_bank_layout.h"

/* SND_fn_pGetBinRes_Bank */
tdstBlockResourceMem *__stdcall SND_fn_pGetBinRes_Bank(unsigned long _ulBinId)
{
    tdstBankElement *bank;
    if (bank_manager) {
        bank = sound_current_bank(bank_manager);
        if (bank && bank->pResMemList)
            return bank->pResMemList + _ulBinId;
    }
    return 0;
}

/* SND_fn_pGetBinEvent_Bank */
SND_tdstBlockEvent *__cdecl SND_fn_pGetBinEvent_Bank(unsigned long _ulBinId)
{
    tdstBankElement *bank;
    if (bank_manager) {
        bank = sound_current_bank(bank_manager);
        if (bank && bank->pEventList)
            return bank->pEventList + _ulBinId;
    }
    return 0;
}
