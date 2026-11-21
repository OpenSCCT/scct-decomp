#include "sound_bank_layout.h"

tdstBlockResourceMem *__stdcall SND_fn_pstGetResFromEdIdSnd_Bank(unsigned long ulEdId)
{
    BankListNode *node = bank_list_first;
    while (node) {
        BankListNode *current = node;
        tdstBankElement *bank;
        node = node->next;
        bank = current->item;
        if (bank->bLoaded) {
            long i;
            for (i = 0; i < bank->pBankHeader->resource_count; ++i) {
                if (bank->pResMemList[i].Id == ulEdId)
                    return &bank->pResMemList[i];
            }
        }
    }
    return 0;
}
