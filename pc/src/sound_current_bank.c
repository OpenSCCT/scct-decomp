/* sound_current_bank.c -- the bank in use */
#include "sound_bank_layout.h"

/* sound_current_bank: a C++ member function; `this` arrives in ECX */
tdstBankElement *__fastcall sound_current_bank(SoundBankManager *manager)
{
    return manager->current;
}
