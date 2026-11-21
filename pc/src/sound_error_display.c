#include "sound_error.h"

void __stdcall SND_fn_vDisplayError(e_uwSndErrNumber eErrNum, const char *message)
{
    sound_report_error(sound_error_label(eErrNum), message);
}

void __stdcall SND_fn_vDisplayErrorEx(e_uwSndErrNumber eErrNum, const char *message,
                                      unsigned long level)
{
    if (SND_g_astErrorOccurArray[eErrNum].bDontDisplayAnyMore) {
        sound_report_error(sound_error_label(eErrNum), message);
        SND_g_astErrorOccurArray[eErrNum].bDontDisplayAnyMore = 1;
    }
}

void __stdcall SND_fn_vDesInitErrorSnd(void)
{
    sound_end_error_display();
}
