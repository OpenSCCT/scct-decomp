#include "sound_bank_layout.h"

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
