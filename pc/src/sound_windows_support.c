#include "sound_memory.h"
#include "sound_win32.h"

int __stdcall SND_fn_bTestSnd_Win32(void)
{
    OSVERSIONINFOA version;
    SND_fn_vMemsetSnd(&version, 0, sizeof(version));
    version.dwOSVersionInfoSize = sizeof(version);
    GetVersionExA(&version);
    return version.dwPlatformId != 0;
}

int __stdcall SND_fn_bTestSnd_WinNT4(void)
{
    OSVERSIONINFOA version;
    SND_fn_vMemsetSnd(&version, 0, sizeof(version));
    version.dwOSVersionInfoSize = sizeof(version);
    GetVersionExA(&version);
    return version.dwPlatformId == VER_PLATFORM_WIN32_NT && version.dwMajorVersion == 4;
}

int __stdcall SND_fn_bIsScriptModeUsed(void)
{
    return 0;
}

int __stdcall SND_fn_bTestSnd_WinMM(const WAVEFORMATEX *format)
{
    WAVEOUTCAPSA caps;
    unsigned long flags[12] = {
        WAVE_FORMAT_1M08, WAVE_FORMAT_1S08, WAVE_FORMAT_1M16, WAVE_FORMAT_1S16,
        WAVE_FORMAT_2M08, WAVE_FORMAT_2S08, WAVE_FORMAT_2M16, WAVE_FORMAT_2S16,
        WAVE_FORMAT_4M08, WAVE_FORMAT_4S08, WAVE_FORMAT_4M16, WAVE_FORMAT_4S16
    };
    unsigned int index;
    if (waveOutGetDevCapsA(WAVE_MAPPER, &caps, sizeof(caps)) == 0) {
        if (format->nSamplesPerSec <= 11025)
            index = 0;
        else if (format->nSamplesPerSec <= 22050)
            index = 4;
        else
            index = 8;
        index += (format->wBitsPerSample / 8 - 1) * 2 + format->nChannels - 1;
        if (caps.dwFormats & flags[index])
            return 1;
    }
    return 0;
}
