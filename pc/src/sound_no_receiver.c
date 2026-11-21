#include "sound_error.h"
#include "sound_micro.h"

__declspec(noinline) void __cdecl Snd_ParConv_ConvertWithNoMicro(const SoundParam *par3D,
                                                                 PrivateSoundParam *par)
{
    par->volume = 0;
    par->pitch = 65536;
    if (!bDisplayed) {
        bDisplayed = 1;
        SND_fn_vDisplayError(E_uwSndGenericWarning, "You should define a microphone to play a 3D Sound");
    }
    switch (par->format) {
    case 1:
        par->position.channels.dolby = 0;
        /* fall through */
    case 0:
        par->position.channels.pan = 64;
        break;
    case 2:
        par->position.angle = 0;
        break;
    }
}
