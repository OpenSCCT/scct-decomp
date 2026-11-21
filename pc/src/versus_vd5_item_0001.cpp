// Work item w3 0001: Versus RVA 0x7c70 (constructor) and 0x7ef0 (per-frame
// tick) of the launcher's main-loop object. Neutral class name: the object
// drives GEngine->Tick, measures the frame rate, pumps window messages and
// runs the SECONDS= / RECORDMOVIE benchmark modes. Both were link-time
// optimised (this passed on the stack). Names follow UE2 where the evidence
// (strings, vtable slots used by UGameEngine) supports it; Tick follows UE2's
// Launch.cpp MainLoop body (GWindowManager, MaxTickRate sleep, message pump).
// Status: 0x7c70 MATCH (try_ltcg.py, /O2 /Gy /GX, root Driver_7c70).
// 0x7ef0 near: the body is instruction-for-instruction retail's, but VC7.0
// gives Tick a dynamically aligned frame (push ebp / and esp,-8) because of the
// double spilled across appSeconds(); retail has a plain esp frame, so ebx/edi
// stay free and its message loop keeps the three API pointers in registers.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef double DOUBLE;
typedef void *HANDLE;

struct LARGE_INTEGER { DWORD LowPart; INT HighPart; };
struct POINT { INT x, y; };
struct MSG { HANDLE hwnd; DWORD message; DWORD wParam; INT lParam; DWORD time; POINT pt; };

extern "C" __declspec(dllimport) DWORD __stdcall GetCurrentThreadId();
extern "C" __declspec(dllimport) HANDLE __stdcall GetCurrentThread();
extern "C" __declspec(dllimport) INT __stdcall QueryPerformanceCounter(LARGE_INTEGER *);
extern "C" __declspec(dllimport) void __stdcall Sleep(DWORD);
extern "C" __declspec(dllimport) INT __stdcall TranslateMessage(const MSG *);
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
extern "C" __declspec(dllimport) INT __cdecl _wtoi(const TCHAR *);
extern "C" __declspec(dllimport) int __cdecl _wcsnicmp(const TCHAR *, const TCHAR *, unsigned int);

// Unicode/ANSI dispatch pointers (PeekMessageX / DispatchMessageX).
extern INT (__stdcall *PeekMessageX)(MSG *, HANDLE, DWORD, DWORD, DWORD);   // 0x10c74c34
extern INT (__stdcall *DispatchMessageX)(const MSG *);                      // 0x10c74bf8

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FOutputDevice;
extern FOutputDevice *GLog;

class FExec
{
public:
    virtual UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar);
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    INT Add(INT Count, INT ElementSize);              // 0x44e0
    void Realloc(INT ElementSize)
    {
        if (Data == 0)
            Data = GMalloc->Malloc(ArrayMax * ElementSize, L"FArray::Add");
        else
            Data = GMalloc->Realloc(Data, ArrayMax * ElementSize, L"FArray");
    }
    void Remove(INT Index, INT Count, INT ElementSize);
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    ~TArray() { Remove(0, ArrayNum, sizeof(T)); }
    INT Add(INT Count) { return FArray::Add(Count, sizeof(T)); }
    INT AddOne()
    {
        INT Index = ArrayNum;
        if ((ArrayNum += 1) > ArrayMax)
        {
            ArrayMax = ArrayNum + 3 * ArrayNum / 8 + 32;
            Realloc(sizeof(T));
        }
        return Index;
    }
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

class FString : public TArray<TCHAR>
{
public:
    FString(const TCHAR *In);                         // 0x46c0
};

template <class T> inline void *operator new(unsigned int Size, TArray<T> &Array)
{
    INT Index = Array.AddOne();
    return &Array(Index);
}
inline void operator delete(void *, void *) {}

class UObjectPad_2c
{
public:
    virtual void Slot00();
    char Pad[0x28];
};
class UViewport : public UObjectPad_2c, public FExec
{
};
class UClient
{
public:
    char Pad[0x2c];
    TArray<UViewport *> Viewports;
};
class UObjectPad_28
{
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
    virtual void Slot04();
    virtual void Slot05();
    virtual void Slot06();
    virtual void Slot07();
    virtual void Slot08();
    virtual void Slot09();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Tick(FLOAT DeltaSeconds);           // slot 0x58
    virtual void Slot23();
    virtual void Slot24();
    virtual void Slot25();
    virtual void Slot26();
    virtual void Slot27();
    virtual void Slot28();
    virtual void Slot29();
    virtual void Slot30();
    virtual void Slot31();
    virtual void Slot32();
    virtual void Slot33();
    virtual void Slot34();
    virtual void Slot35();
    virtual void Slot36();
    virtual void Slot37();
    virtual void Slot38();
    virtual void Slot39();
    virtual FLOAT GetMaxTickRate();                  // slot 0xa0
    char Pad[0x24];
};
class UEngine : public UObjectPad_28, public FExec
{
public:
    DWORD Pad2c;
    UClient *Client;                                  // +0x30
    char Pad34[0xa8 - 0x34];
    FLOAT CurrentTickRate;                            // +0xa8
};

// Log window; +0x9c is its exec target.
class WLog
{
public:
    char Pad[0x9c];
    FExec *Exec;
};
extern WLog *GLogWindow;                              // 0x10c91c88
extern UEngine *GWindowManager;                     // 0x10c966d8 (UE2 MainLoop ticks it too)
extern UBOOL GIsRunning;                              // 0x10c9690c
extern UBOOL GIsRequestingExit;                       // 0x10c96918
extern UBOOL GTimestamp;                              // 0x10c94688 (use QueryPerformanceCounter)
extern TCHAR GCmdLine[];                              // 0x10c92680
extern INT GFrameCounter;                             // 0x10ccb43c (unidentified)

struct FStats
{
    char Pad[0x24];
    TArray<INT> DWORDStats;                           // +0x24
    char Pad30[0x134 - 0x30];
    INT STATS_Frame_TotalCycles;                      // +0x134
};
extern FStats GStats;                                 // 0x10cbf650
void __stdcall FStats_Clear(FStats *Stats);           // 0x1ce190 (unidentified, this on stack)

double appSeconds();                                  // 0x4030
const TCHAR *appStrfind(const TCHAR *Str, const TCHAR *Find);   // 0x11f90

template <class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }
inline void appSleep(FLOAT Seconds) { Sleep((DWORD)(Seconds * 1000.0)); }
inline const TCHAR *appCmdLine() { return GCmdLine; }
inline DWORD appCycles()
{
    if (GTimestamp)
    {
        LARGE_INTEGER Cycles;
        QueryPerformanceCounter(&Cycles);
        return Cycles.LowPart;
    }
    __asm rdtsc
}
inline UBOOL Parse(const TCHAR *Stream, const TCHAR *Match, INT &Value)
{
    const TCHAR *Temp = appStrfind(Stream, Match);
    if (Temp == 0)
        return 0;
    Temp += wcslen(Match);
    Value = _wtoi(Temp);
    return 1;
}
inline UBOOL ParseParam(const TCHAR *Stream, const TCHAR *Param)
{
    const TCHAR *Start = Stream;
    if (*Stream)
    {
        while ((Start = appStrfind(Start + 1, Param)) != 0)
        {
            if (Start > Stream && (Start[-1] == '-' || Start[-1] == '/'))
                return 1;
        }
    }
    return 0;
}

class UnnamedEngineLoop_7c70
{
public:
    UEngine *Engine;                                  // +0x00
    UBOOL PumpMessages;                               // +0x04
    DWORD ThreadId;                                   // +0x08
    HANDLE Thread;                                    // +0x0c
    DOUBLE LastTime;                                  // +0x10
    DOUBLE FPSTime;                                   // +0x18
    INT FPSFrames;                                    // +0x20
    DWORD LastCycles;                                 // +0x24
    INT BenchFrame;                                   // +0x28
    INT BenchStartFrame;                              // +0x2c
    INT BenchEndFrame;                                // +0x30
    FLOAT BenchTime;                                  // +0x34
    TArray<FString> FrameNames;                       // +0x38
    TArray<INT> FrameTimes;                           // +0x44
    UBOOL RecordMovie;                                // +0x50

    UnnamedEngineLoop_7c70(UEngine *InEngine, UBOOL InPumpMessages);
    void Tick();
    ~UnnamedEngineLoop_7c70();                        // 0x8150
};

// RVA 0x7c70
UnnamedEngineLoop_7c70::UnnamedEngineLoop_7c70(UEngine *InEngine, UBOOL InPumpMessages)
    : Engine(InEngine), PumpMessages(InPumpMessages)
{
    if (GLogWindow)
        GLogWindow->Exec = Engine;
    GIsRunning = 1;
    ThreadId = GetCurrentThreadId();
    Thread = GetCurrentThread();
    LastTime = appSeconds();
    FPSTime = LastTime;
    FPSFrames = 0;
    BenchFrame = 0;
    BenchStartFrame = 10;
    BenchTime = 0;
    BenchEndFrame = 0;
    Parse(appCmdLine(), L"SECONDS=", BenchEndFrame);
    BenchEndFrame *= 30;
    for (INT i = 0; i < BenchEndFrame - BenchStartFrame + 1; i++)
        new(FrameNames) FString(L"");
    if (BenchEndFrame)
        FrameTimes.Add(BenchEndFrame - BenchStartFrame + 1);
    LastCycles = appCycles();
    RecordMovie = ParseParam(appCmdLine(), L"RECORDMOVIE");
}

// RVA 0x7ef0
void UnnamedEngineLoop_7c70::Tick()
{
    if (!GIsRunning || GIsRequestingExit)
        return;
    GFrameCounter++;
    FStats_Clear(&GStats);
    DOUBLE Now = appSeconds();
    FLOAT DeltaTime = Now - LastTime;
    if (RecordMovie)
    {
        Engine->Tick(1.f / 30.f);
        if (GWindowManager)
            GWindowManager->Tick(1.f / 30.f);
        if (BenchFrame < BenchEndFrame)
            BenchTime += DeltaTime;
        BenchFrame++;
    }
    else
    {
        Engine->Tick(DeltaTime);
        if (GWindowManager)
            GWindowManager->Tick(DeltaTime);
    }
    FPSFrames++;
    LastTime = Now;
    if (FPSTime + 1.0 < LastTime)
    {
        Engine->CurrentTickRate = FPSFrames / (LastTime - FPSTime);
        FPSTime = LastTime;
        FPSFrames = 0;
    }
    if (PumpMessages)
    {
        FLOAT MaxTickRate = Engine->GetMaxTickRate();
        if (MaxTickRate > 0.0)
        {
            FLOAT Delta = (1.0 / MaxTickRate) - (appSeconds() - LastTime);
            appSleep(Max(0.f, Delta));
        }
        if (PumpMessages)
        {
            MSG Msg;
            while (PeekMessageX(&Msg, 0, 0, 0, 1))
            {
                if (Msg.message == 0x12)
                    GIsRequestingExit = 1;
                TranslateMessage(&Msg);
                DispatchMessageX(&Msg);
            }
        }
    }
    if (RecordMovie)
        Engine->Client->Viewports(0)->Exec(L"shot", *GLog);
    GStats.DWORDStats(GStats.STATS_Frame_TotalCycles) = appCycles() - LastCycles;
    LastCycles = appCycles();
}

// Scaffolding for the link, not part of the unit.
// appStrfind (0x11f90) is defined so the linker gives it retail's register
// convention (Str in EAX).
const TCHAR *appStrfind(const TCHAR *Str, const TCHAR *Find)
{
    UBOOL Alnum = 0;
    TCHAR f = (*Find < 'a' || *Find > 'z') ? (*Find) : (*Find + 'A' - 'a');
    INT Length = (INT)wcslen(Find++) - 1;
    TCHAR c = *Str++;
    while (c)
    {
        if (c >= 'a' && c <= 'z')
            c += 'A' - 'a';
        if (!Alnum && c == f && !_wcsnicmp(Str, Find, Length))
            return Str - 1;
        Alnum = (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
        c = *Str++;
    }
    return 0;
}
void Escape(void *);
inline void *operator new(unsigned int, void *Memory) { return Memory; }
UnnamedEngineLoop_7c70 *Driver_7c70(void *Memory, UEngine *Engine, UBOOL Pump)
{
    Escape(&GMalloc); Escape(&GLogWindow); Escape(&GIsRunning); Escape(&GTimestamp); Escape(GCmdLine);
    return new (Memory) UnnamedEngineLoop_7c70(Engine, Pump);
}
void Driver_7ef0(UnnamedEngineLoop_7c70 *Loop)
{
    // Retail's caller keeps an 8-byte aligned stack, so LTCG does not realign
    // Tick's frame; this double gives the driver the same property.
    DOUBLE Aligned = appSeconds();
    Escape(&Aligned);
    Escape(&GIsRunning); Escape(&GIsRequestingExit); Escape(&GFrameCounter); Escape(&GWindowManager);
    Escape(&GTimestamp); Escape(&GStats); Escape(&GLog); Escape(&PeekMessageX); Escape(&DispatchMessageX);
    Loop->Tick();
}
