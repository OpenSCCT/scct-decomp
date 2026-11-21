/* sound_error.h -- error and warning reports of the sound library (snderr.c) */
#ifndef SOUND_ERROR_H
#define SOUND_ERROR_H

/* Enumerator names are those of the sibling build's e_uwSndErrNumber_; the values are the
   ones this build's label table pairs with the same messages. This build numbers one more
   error than the sibling from 20 on; 20 itself has no label and no known name, and nothing
   above 42 has a label to identify it by. */
typedef enum e_uwSndErrNumber_ {
    E_uwSndFatalErr = 0,
    E_uwSndMemoryBlockError = 1,
    E_uwSndThreadDeadLockError = 2,
    E_uwSndThreadReentranceDetectedError = 3,
    E_uwSndInitNotDoneError = 4,
    E_uwSndBadHostConfiguration = 5,
    E_uwSndFatalError4 = 6,
    E_uwSndStartOfWarning = 7,
    E_uwSndGenericWarning = 8,
    E_uwSndObsoletDataFormat = 9,
    E_uwSndMemoryAllocError = 10,
    E_uwSndMemoryReAllocError = 11,
    E_uwSndCannotOpenFile = 12,
    E_uwSndErrorReadingFile = 13,
    E_uwSndINIFileNotFound = 14,
    E_uwSndScriptLoadError = 15,
    E_uwSndDLLCannotFindFunction = 16,
    E_uwSndDLLCannotLoadDLL = 17,
    E_uwSndEndOfWarningLevel2 = 18,
    E_uwSndResourceMissing = 19,
    E_uwSndTooManyEvents = 21,
    E_uwSndInvalidTypeOfEvent = 22,
    E_uwSndTooManyVoices = 23,
    E_uwSndInvalidTypeOfResource = 24,
    E_uwSndTooManySequences = 25,
    E_uwSndTooManySamples = 26,
    E_uwSndTooManySwitchs = 27,
    E_uwSndTooManySplits = 28,
    E_uwSndInvalidDynParamForResource = 29,
    E_uwSndInvalidStaticParamForResource = 30,
    E_uwSndThreadMultiThreadDetectedError = 31,
    E_uwSndSystemError = 32,
    E_uwSndWaveCreateThread = 33,
    E_uwSndCreateThread = 34,
    E_uwSndBankEditionError = 35,
    E_uwSndMixerNoMixer = 36,
    E_uwSndMixerNoId = 37,
    E_uwSndMixerOpen = 38,
    E_uwSndMixerCapacities = 39,
    E_uwSndMixerDesinit = 40,
    E_uwSndEventNotInABank = 41,
    E_uwSndEventUsesUnloadedBank = 42
} e_uwSndErrNumber;

void __stdcall SND_fn_vDisplayError(e_uwSndErrNumber eErrNum, const char *message);
/* guess: the last argument is a warning level; every recovered caller passes 3. */
void __stdcall SND_fn_vDisplayErrorEx(e_uwSndErrNumber eErrNum, const char *message,
                                      unsigned long level);
void __stdcall SND_fn_vDesInitErrorSnd(void);

#endif
