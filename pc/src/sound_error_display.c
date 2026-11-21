/* sound_error_display.c -- reports errors and warnings (snderr.c) */
#include "sound_error.h"

/* SND_fn_vDisplayError */
void __stdcall SND_fn_vDisplayError(e_uwSndErrNumber eErrNum, const char *message)
{
    sound_report_error(sound_error_label(eErrNum), message);
}

/* SND_fn_vDisplayErrorEx: reports only while the error's entry in the occurrence array is set */
void __stdcall SND_fn_vDisplayErrorEx(e_uwSndErrNumber eErrNum, const char *message,
                                      unsigned long level)
{
    if (SND_g_astErrorOccurArray[eErrNum].bDontDisplayAnyMore) {
        sound_report_error(sound_error_label(eErrNum), message);
        SND_g_astErrorOccurArray[eErrNum].bDontDisplayAnyMore = 1;
    }
}

/* SND_fn_vDesInitErrorSnd */
void __stdcall SND_fn_vDesInitErrorSnd(void)
{
    sound_end_error_display();
}
