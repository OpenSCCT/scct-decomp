#include "sound_bank_layout.h"
#include "sound_error.h"
#include "sound_name_tree.h"
#include "sound_string.h"
#include "sound_thread.h"

unsigned long __stdcall SND_fn_ulGetEditorIdFromSoundEventName(const char *szName)
{
    char message[256];
    unsigned long id;
    SoundNameArg key = { szName };
    SND_fn_vEnterCriticalSectionThreadSnd_();
    SND_fn_vMouchardThreadsnd(SNDLDBIN_C_FILE, 1339);
    if (!sound_get_event_name_support()) {
        SND_fn_vQuitCriticalSectionThreadSnd();
        SND_fn_vStrncpy(message, "ERROR: Check if you forget to enable the support of event name in binary !",
                        sizeof(message));
        SND_fn_vDisplayErrorEx(E_uwSndGenericWarning, message, 3);
        return (unsigned long)-1;
    }
    id = sound_lookup_event_name(sound_event_names, key);
    SND_fn_vQuitCriticalSectionThreadSnd();
    return id;
}
