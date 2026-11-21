// Work item 0191: Versus RVA 0xe2ab0-0xe2fb3, UClient (Engine UnClient.cpp).
// 0xe2ab0: UClient::Exec(const TCHAR *Cmd, FOutputDevice &Ar)
// 0xe2ea0: UClient::Flush(UBOOL AllowPrecache)
// 0xe2ed0: UClient::UpdateGamma()
// 0xe2f10: UClient::RestoreGamma()
// 0xe2f40: UClient::Serialize(FArchive &Ar)
// 0xe2f80: TObjectIterator<UTexture>::operator++()

typedef unsigned short TCHAR;
typedef char ANSICHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

extern "C" __declspec(dllimport) double __cdecl atof(const char *);
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
extern "C" __declspec(dllimport) INT __cdecl _wcsnicmp(const TCHAR *, const TCHAR *, unsigned int);

inline INT appStrlen(const TCHAR *S) { return (INT)wcslen(S); }
inline INT appStrnicmp(const TCHAR *A, const TCHAR *B, INT Count) { return _wcsnicmp(A, B, Count); }
inline UBOOL appIsAlnum(TCHAR c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

ANSICHAR *appToAnsi(const TCHAR *Str, ANSICHAR *ACh = 0);

// ---- Core containers & strings ----
class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    INT Add(INT Count, INT ElementSize);
    void Empty(INT ElementSize, INT Slack);
};

template<class T> class TArray : public FArray
{
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((const T *)Data)[i]; }
};

class FString : public TArray<TCHAR>
{
public:
    FString() {}
    FString(const TCHAR *In);
    ~FString();
    FString &operator=(const FString &Other);
    const TCHAR *operator*() const { return Num() ? &(*this)(0) : L""; }
    static FString __cdecl Printf(const TCHAR *Fmt, ...);
};

struct FName
{
    INT Index;
    FName() {}
    FName(INT InIndex) : Index(InIndex) {}
};

enum EName
{
    NAME_None = 0,
    ENGINE_ClientMessage = 0xb4d,
};

enum EPropertyFlags
{
    CPF_Config = 0x00004000,
};

class FOutputDevice;
class UClass;
class UViewport;
class APlayerController;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    virtual void Slot08();
    virtual void Slot0c();
    virtual void Slot10();
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    virtual FArchive &operator<<(class UObject *&Res);

    INT ArVer, ArNetVer, ArLicenseeVer, ArIsLoading, ArIsSaving, ArIsTrans, ArIsPersistent;
    INT ArForEdit, ArForClient, ArForServer, ArIsError, ArIsCriticalError, ArContainsCode;
    INT ArFlags3, ArMaxSerializeSize;
};

FArchive &operator<<(FArchive &Ar, TArray<UViewport *> &A);

class UObject
{
public:
    virtual ~UObject();
    virtual void Slot04();
    virtual void Slot08();
    virtual void Slot0c();
    virtual void ProcessEvent(void *Function, void *Parms, void *UnusedResult = 0); // +0x10
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1c();
    virtual void Slot20();
    virtual void Slot24();
    virtual void Serialize(FArchive &Ar); // +0x28

    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    FName Name;
    UClass *Class;

    UBOOL IsA(UClass *SomeBase) const;
    void __stdcall SaveConfig(DWORD Flags = CPF_Config, const TCHAR *Filename = 0, UBOOL bForce = 1);
    void *FindFunctionChecked(FName InName, INT Global = 0);

    static TArray<UObject *> GObjObjects;
};

class UClass : public UObject
{
public:
    UClass *SuperField; // +0x28
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return SomeBase == 0;
}

class URenderDevice : public UObject
{
public:
    virtual void Slot2c(); virtual void Slot30(); virtual void Slot34(); virtual void Slot38();
    virtual void Slot3c(); virtual void Slot40(); virtual void Slot44(); virtual void Slot48();
    virtual void Slot4c(); virtual void Slot50(); virtual void Slot54(); virtual void Slot58();
    virtual void Slot5c(); virtual void Slot60(); virtual void Slot64(); virtual void Slot68();
    virtual void Slot6c(); virtual void Slot70(); virtual void Slot74();
    virtual void Flush(UViewport *Viewport);        // +0x78
    virtual void Slot7c(); virtual void Slot80();
    virtual void UpdateGamma(UViewport *Viewport);  // +0x84
    virtual void RestoreGamma();                    // +0x88
};

struct APlayerController_eventClientMessage_Parms
{
    FString S;
    FName Type;
};

class APlayerController : public UObject
{
public:
    void eventClientMessage(const FString &S, FName Type = NAME_None);
};

class UViewport : public UObject
{
public:
    DWORD Pad28[2];
    APlayerController *Actor;   // +0x30
    DWORD Pad34[(0x70 - 0x34) / 4];
    URenderDevice *RenDev;      // +0x70
};

class UTexture : public UObject
{
public:
    DWORD Pad28[(0xb4 - 0x28) / 4];
    DWORD Flags;                // +0xb4

    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

class UEngine : public UObject
{
public:
    virtual void Slot2c(); virtual void Slot30(); virtual void Slot34(); virtual void Slot38();
    virtual void Slot3c(); virtual void Slot40(); virtual void Slot44(); virtual void Slot48();
    virtual void Slot4c(); virtual void Slot50(); virtual void Slot54(); virtual void Slot58();
    virtual void Slot5c(); virtual void Slot60(); virtual void Slot64(); virtual void Slot68();
    virtual void Slot6c();
    virtual void UpdateGamma(); // +0x70
};

class UClient : public UObject
{
public:
    virtual void Slot2c(); virtual void Slot30(); virtual void Slot34(); virtual void Slot38();
    virtual void Slot3c(); virtual void Slot40(); virtual void Slot44(); virtual void Slot48();
    virtual void Slot4c(); virtual void Slot50(); virtual void Slot54(); virtual void Slot58();
    virtual void Flush(UBOOL AllowPrecache); // +0x5c
    virtual void UpdateGamma();              // +0x60
    virtual void RestoreGamma();             // +0x64

    virtual void Serialize(FArchive &Ar);    // +0x28 (override)
    UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar);

    UEngine *Engine;                    // +0x28
    TArray<UViewport *> Viewports;      // +0x2c
    DWORD Pad38[(0x70 - 0x38) / 4];
    FLOAT Brightness;                   // +0x70
    FLOAT Contrast;                     // +0x74
    FLOAT Gamma;                        // +0x78
};

template<class T> class TObjectIterator
{
public:
    TObjectIterator()
        : Array(&UObject::GObjObjects), Index(-1)
    {
        ++*this;
    }
    TObjectIterator<T> &operator++();
    operator UBOOL() { return Index < Array->Num(); }
    T *operator*() { return (T *)(*Array)(Index); }
    T *operator->() { return (T *)(*Array)(Index); }
protected:
    TArray<UObject *> *Array;
    INT Index;
};

// RVA 0xe2f80
template<class T> TObjectIterator<T> &TObjectIterator<T>::operator++()
{
    while (++Index < Array->Num() && (!(*Array)(Index) || !(*Array)(Index)->IsA(T::StaticClass())))
        ;
    return *this;
}

template<class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

double appAtof(const TCHAR *String);

UBOOL ParseCommand(const TCHAR **Stream, const TCHAR *Match);

// Retail keeps these literals in writable .data.
extern const TCHAR TEXT_BRIGHTNESS[];
extern const TCHAR TEXT_BrightnessFmt[];
extern const TCHAR TEXT_CONTRAST[];
extern const TCHAR TEXT_ContrastFmt[];
extern const TCHAR TEXT_GAMMA[];
extern const TCHAR TEXT_GammaFmt[];

// RVA 0xe2ea0
void UClient::Flush(UBOOL AllowPrecache)
{
    for (INT i = 0; i < Viewports.Num(); i++)
        if (Viewports(i)->RenDev)
            Viewports(i)->RenDev->Flush(Viewports(i));
}

// RVA 0xe2ed0
void UClient::UpdateGamma()
{
    for (INT i = 0; i < Viewports.Num(); i++)
        if (Viewports(i)->RenDev)
            Viewports(i)->RenDev->UpdateGamma(Viewports(i));
}

// RVA 0xe2f10
void UClient::RestoreGamma()
{
    for (INT i = 0; i < Viewports.Num(); i++)
        if (Viewports(i)->RenDev)
            Viewports(i)->RenDev->RestoreGamma();
}

// RVA 0xe2f40
void UClient::Serialize(FArchive &Ar)
{
    UObject::Serialize(Ar);
    Ar << Viewports;
}

// RVA 0xe2ab0
// Retail's LTCG link expanded appAtof(Cmd) (atof(appToAnsi(Cmd))) at the
// BRIGHTNESS and CONTRAST call sites and left the GAMMA site out of line.
UBOOL UClient::Exec(const TCHAR *Cmd, FOutputDevice &Ar)
{
    if (ParseCommand(&Cmd, TEXT_BRIGHTNESS))
    {
        if (*Cmd == '+')
            Brightness = Brightness >= 0.9f ? 0.0f : Brightness + 0.1f;
        else if (*Cmd)
            Brightness = Clamp<FLOAT>((FLOAT)atof(appToAnsi(Cmd)), 0.f, 1.f);
        else
            Brightness = 0.5f;
        Engine->UpdateGamma();
        SaveConfig();
        if (Viewports.Num() && Viewports(0)->Actor)
            Viewports(0)->Actor->eventClientMessage(*FString::Printf(TEXT_BrightnessFmt, (INT)(Brightness * 10)));
        return 1;
    }
    else if (ParseCommand(&Cmd, TEXT_CONTRAST))
    {
        if (*Cmd == '+')
            Contrast = Contrast >= 1.9f ? 0.0f : Contrast + 0.1f;
        else if (*Cmd)
            Contrast = Clamp<FLOAT>((FLOAT)atof(appToAnsi(Cmd)), 0.f, 2.f);
        else
            Contrast = 0.5f;
        Engine->UpdateGamma();
        SaveConfig();
        if (Viewports.Num() && Viewports(0)->Actor)
            Viewports(0)->Actor->eventClientMessage(*FString::Printf(TEXT_ContrastFmt, (INT)(Contrast * 10)));
        return 1;
    }
    else if (ParseCommand(&Cmd, TEXT_GAMMA))
    {
        if (*Cmd == '+')
            Gamma = Gamma >= 2.4f ? 0.5f : Gamma + 0.1f;
        else if (*Cmd)
            Gamma = Clamp<FLOAT>((FLOAT)appAtof(Cmd), 0.5f, 2.5f);
        else
            Gamma = 1.7f;
        Engine->UpdateGamma();
        SaveConfig();
        if (Viewports.Num() && Viewports(0)->Actor)
            Viewports(0)->Actor->eventClientMessage(*FString::Printf(TEXT_GammaFmt, Gamma));
        return 1;
    }
    else return 0;
}

// ---- Scaffolding for LTCG link, not part of the unit ----
void Escape(void *);
inline void *operator new(unsigned int, void *Mem) { return Mem; }

__declspec(noinline) FArchive &SerializeIndex(FArchive &Ar, INT &Value)
{
    if (!Ar.ArIsLoading && !Ar.ArIsSaving) {
        Ar.Serialize(&Value, sizeof(INT));
        return Ar;
    }
    DWORD V = Value >= 0 ? Value : -Value;
    unsigned char B0 = (unsigned char)((Value >= 0 ? 0 : 0x80) + (V < 0x40 ? V : (V & 0x3f) + 0x40));
    Value = 0;
    Ar.Serialize(&B0, 1);
    if (B0 & 0x40) {
        V >>= 6;
        unsigned char B1 = (unsigned char)(V < 0x80 ? V : (V & 0x7f) + 0x80);
        Ar.Serialize(&B1, 1);
        if (B1 & 0x80) {
            V >>= 7;
            unsigned char B2 = (unsigned char)(V < 0x80 ? V : (V & 0x7f) + 0x80);
            Ar.Serialize(&B2, 1);
            if (B2 & 0x80) {
                V >>= 7;
                unsigned char B3 = (unsigned char)(V < 0x80 ? V : (V & 0x7f) + 0x80);
                Ar.Serialize(&B3, 1);
                if (B3 & 0x80) {
                    V >>= 7;
                    unsigned char B4 = (unsigned char)V;
                    Ar.Serialize(&B4, 1);
                    Value = B4;
                }
                Value = (Value << 7) + (B3 & 0x7f);
            }
            Value = (Value << 7) + (B2 & 0x7f);
        }
        Value = (Value << 7) + (B1 & 0x7f);
    }
    Value = (Value << 6) + (B0 & 0x3f);
    if (B0 & 0x80)
        Value = -Value;
    return Ar;
}

__declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray<UViewport *> &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(UViewport *), A.ArrayMax * sizeof(UViewport *));
    if (Ar.ArIsLoading) {
        INT NewNum;
        SerializeIndex(Ar, NewNum);
        A.Empty(sizeof(UViewport *), NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << *(UObject **)&A(A.FArray::Add(1, sizeof(UViewport *)));
    } else {
        SerializeIndex(Ar, A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << *(UObject **)&A(i);
    }
    return Ar;
}

UBOOL ParseCommand(const TCHAR **Stream, const TCHAR *Match)
{
    while ((**Stream == ' ') || (**Stream == 9))
        (*Stream)++;
    if (appStrnicmp(*Stream, Match, appStrlen(Match)) == 0)
    {
        *Stream += appStrlen(Match);
        if (!appIsAlnum(**Stream))
        {
            while ((**Stream == ' ') || (**Stream == 9))
                (*Stream)++;
            return 1;
        }
        else
        {
            *Stream -= appStrlen(Match);
            return 0;
        }
    }
    return 0;
}

void APlayerController::eventClientMessage(const FString &S, FName Type)
{
    APlayerController_eventClientMessage_Parms Parms;
    Parms.S = S;
    Parms.Type = Type;
    ProcessEvent(FindFunctionChecked(ENGINE_ClientMessage), &Parms);
}

void Driver_e2f40(void *Mem, UClient *C, FArchive &Ar)
{
    Escape(new (Mem) UClient);
    C->UClient::Serialize(Ar);
}

__declspec(noinline) double appAtof(const TCHAR *String)
{
    return atof(appToAnsi(String));
}

void Driver_e2f80(TObjectIterator<UTexture> *It)
{
    Escape(&UObject::GObjObjects);
    Escape(&UTexture::PrivateStaticClass);
    ++*It;
}

UBOOL Driver_e2ab0(UClient *C, const TCHAR *Cmd, FOutputDevice &Ar)
{
    Escape((void *)&TEXT_BRIGHTNESS);
    Escape((void *)&TEXT_BrightnessFmt);
    Escape((void *)&TEXT_CONTRAST);
    Escape((void *)&TEXT_ContrastFmt);
    Escape((void *)&TEXT_GAMMA);
    Escape((void *)&TEXT_GammaFmt);
    return C->Exec(Cmd, Ar);
}
