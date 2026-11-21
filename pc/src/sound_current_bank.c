#include "sound_bank_layout.h"

tdstBankElement *__fastcall sound_current_bank(SoundBankManager *manager)
{
    return manager->current;
}
