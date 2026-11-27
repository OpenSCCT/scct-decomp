#include "versus_build.h"
#include "versus_native_class_init.h"
#include "versus_output_device.h"
#include <stdarg.h>

extern "C" __declspec(dllimport) INT __cdecl _vsnwprintf(TCHAR *Buffer, unsigned int Count,
    const TCHAR *Format, va_list Args);
extern TArray<FNameEntry *> FName_Names;
extern TCHAR GCmdLine[];
extern const TCHAR ObjectAllocationTag[] = L"new";
TCHAR NoFlushParameter[] = L"NOFLUSH";
UBOOL ParseParam(const TCHAR *Stream, const TCHAR *Param);

void FOutputDevice::Logf(EName Event, const TCHAR *Format, ...)
{
    const DWORD RF_Suppress = 0x1000;
    const INT BufferChars = 32768;
    if (!FName::Initialized || !(FName_Names(Event)->Flags & RF_Suppress)) {
        TCHAR *Buffer = static_cast<TCHAR *>(GMalloc->Malloc(BufferChars * sizeof(TCHAR),
            ObjectAllocationTag));
        va_list Args;
        va_start(Args, Format);
        _vsnwprintf(Buffer, BufferChars, Format, Args);
        va_end(Args);
        Serialize(Buffer, Event);
        GMalloc->Free(Buffer);
    }
    if (!ParseParam(GCmdLine, NoFlushParameter))
        Flush();
}

struct FFrame : public FOutputDevice {
    UStruct *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;
};

static const EName NAME_Critical = static_cast<EName>(589);

void UObject::execUndefined(FFrame &Stack, void *const Result)
{
    Stack.Logf(NAME_Critical, L"Unknown code token %02X", Stack.Code[-1]);
}
