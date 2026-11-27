#include "versus_build.h"
#include "versus_native_subsystem.h"
#include "versus_stats_data.h"

void appMemcpy(void *Dest, const void *Src, INT Count);
// Retail has a distinct zero-initialized TCHAR in writable static storage.
TCHAR EmptyStatString[1];

#include "versus_app_memzero.h"

void FStats::Clear()
{
    if (Integers.Current.Num())
        appMemcpy(Integers.Previous.Data, Integers.Current.Data,
                  Integers.Current.Num() * sizeof(DWORD));
    if (Floats.Current.Num())
        appMemcpy(Floats.Previous.Data, Floats.Current.Data,
                  Floats.Current.Num() * sizeof(FLOAT));
    for (INT i = 0; i < Strings.Current.Num(); ++i)
        Strings.Previous(i) = Strings.Current(i);

    if (Integers.Current.Num())
        appMemzero(Integers.Current.Data, Integers.Current.Num() * sizeof(DWORD));
    if (Floats.Current.Num())
        appMemzero(Floats.Current.Data, Floats.Current.Num() * sizeof(FLOAT));
    for (i = 0; i < Strings.Current.Num(); ++i)
        Strings.Current(i) = EmptyStatString;
}

#include "versus_commandlet.h"

extern UBOOL GIsRunning;
class FConfigCache
{
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual const TCHAR* GetStr(const TCHAR* Section, INT Unknown1, const TCHAR* Key, INT Unknown2);
};

extern FConfigCache* GConfig;
extern FOutputDevice* GError;
extern UObject* GObjTransientPkg;
extern UBOOL GIsRequestingExit;
extern DWORD GUnknown_96910;

DOUBLE appSeconds();
extern "C" __declspec(dllimport) void __stdcall Sleep(DWORD dwMilliseconds);

inline void appSleep(FLOAT Seconds)
{
    Sleep((DWORD)(Seconds * 1000.0));
}
template<class T> inline T Max(const T A, const T B)
{
    return (A >= B) ? A : B;
}

class UEngine : public USubsystem
{
public:
    static UClass PrivateStaticClass;

    virtual void Init();                     // 0x5c
    virtual void ESlot24();
    virtual void ESlot25();
    virtual void ESlot26();
    virtual void ESlot27();
    virtual void ESlot28();
    virtual void ESlot29();
    virtual void ESlot30();
    virtual void ESlot31();
    virtual void ESlot32();
    virtual void ESlot33();
    virtual void ESlot34();
    virtual void ESlot35();
    virtual void ESlot36();
    virtual void ESlot37();
    virtual void ESlot38();
    virtual void ESlot39();
    virtual FLOAT GetMaxTickRate();          // 0xa0
    DWORD UEngineData[32];
    FLOAT CurrentTickRate;                   // 0xa8
};

template<class T>
T *ConstructObject(UClass *Class, UObject *Outer = GObjTransientPkg, FName Name = NAME_None,
                   DWORD Flags = 0, UObject *Template = 0, FOutputDevice *Error = GError,
                   UObject *Ptr = 0, UObject *SubobjectRoot = 0)
{
    T *Result = (T *)UObject::StaticAllocateObject(Class, Outer, Name, Flags, Template, Error, Ptr, SubobjectRoot);
    if (Result)
        (*Class->ClassConstructor)(Result);
    return Result;
}

#include "versus_server_object_loading.inl"

INT UServerCommandlet::Main(const TCHAR* Parms)
{
    const EName EnginePackage = (EName)21;
    const EName GameEngineClass = (EName)196;
    GUnknown_96910 = 3;
    if (const TCHAR* Language = GConfig->GetStr(L"Engine.Engine", 0, L"Language", 0))
        UObject::SetLanguage(Language);

    UClass *EngineClass = UObject::StaticLoadClass(&UEngine::PrivateStaticClass, 0, EnginePackage, NAME_None, GameEngineClass, 0, 1, 0);
    UEngine *Engine = ConstructObject<UEngine>(EngineClass);
    Engine->Init();

    GIsRunning = 1;
    DOUBLE OldTime = appSeconds();
    DOUBLE SecondStartTime = OldTime;
    INT TickCount = 0;
    while (GIsRunning && !GIsRequestingExit)
    {
        GStats.Clear();

        DOUBLE NewTime = appSeconds();
        Engine->Tick(NewTime - OldTime);
        OldTime = NewTime;
        TickCount++;
        if (OldTime > SecondStartTime + 1)
        {
            Engine->CurrentTickRate = (FLOAT)TickCount / (OldTime - SecondStartTime);
            SecondStartTime = OldTime;
            TickCount = 0;
        }

        FLOAT MaxTickRate = Engine->GetMaxTickRate();
        if (MaxTickRate > 0.0f)
        {
            FLOAT Delta = (1.0f / MaxTickRate) - (appSeconds() - OldTime);
            appSleep(Max(0.f, Delta));
        }
    }
    GIsRunning = 0;
    return 0;
}
