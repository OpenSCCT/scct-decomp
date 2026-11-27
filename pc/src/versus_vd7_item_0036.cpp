// w4_item_0036.cpp -- Versus work item 0036: AGameInfo script natives (0x129ab0-0x129e5f)
#pragma pack(push, 4)

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

extern "C" __declspec(dllimport) const TCHAR *__cdecl wcsstr(const TCHAR *String, const TCHAR *Find);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcsncpy(TCHAR *Dest, const TCHAR *Src, unsigned int Count);

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

inline const TCHAR *appStrstr(const TCHAR *String, const TCHAR *Find)
{
    return wcsstr(String, Find);
}

inline TCHAR *appStrncpy(TCHAR *Dest, const TCHAR *Src, INT MaxLen)
{
    wcsncpy(Dest, Src, MaxLen);
    Dest[MaxLen - 1] = 0;
    return Dest;
}

template<class T> inline T Clamp(T X, T Min, T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

// Writable .data literals in retail Versus
extern const TCHAR GEmptyString[];        // 0x10c92310: L""
extern const TCHAR GKillMsgKillerToken[]; // 0x10c47b00: L"%k"
extern const TCHAR GKillMsgVictimToken[]; // 0x10c47b08: L"%o"

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray()
        : Data(0)
        , ArrayNum(0)
        , ArrayMax(0)
    {
    }

    FArray(INT InNum, INT ElementSize)
        : ArrayNum(InNum)
        , ArrayMax(InNum)
    {
        if (!ArrayMax)
            Data = 0;
        else
            Data = GMalloc->Malloc(ArrayMax * ElementSize, L"Farray::protectedcstor");
    }
};

class FString : protected FArray
{
public:
    FString() {}
    FString(const TCHAR *In);
    // Out-of-line in retail Core (0x4af0); noinline keeps LTCG from folding it into FString::Left.
    __declspec(noinline) FString(INT InCount, const TCHAR *InSrc);
    ~FString();

    FString &operator=(const FString &Other);
    FString &operator+=(const TCHAR *Str);
    FString &operator+=(const FString &Str)
    {
        return operator+=(*Str);
    }

    const TCHAR *operator*() const
    {
        return ArrayNum ? (const TCHAR *)Data : L"";
    }

    INT Len() const
    {
        return ArrayNum ? ArrayNum - 1 : 0;
    }

    FString Left(INT Count) const;
    FString Right(INT Count) const;

    INT InStr(const TCHAR *SubStr) const
    {
        const TCHAR *Tmp = appStrstr(**this, SubStr);
        return Tmp ? (INT)(Tmp - **this) : -1;
    }
};

class UObject
{
public:
    virtual ~UObject();
};

class UStruct;
struct FFrame;

class __declspec(novtable) FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, INT Event) = 0;
};

typedef void (UObject::*Native)(FFrame &Stack, void *const Result);
extern Native GNatives[];

struct FFrame : public FOutputDevice
{
    UStruct *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;

    void Step(UObject *Context, void *const Result)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_STR(Var) FString Var; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

class UNetDriver : public UObject
{
public:
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual FString LowLevelGetNetworkNumber();
};

class ULevel : public UObject
{
public:
    BYTE unk_04[0xe8];
    UNetDriver *NetDriver;
};

class AActor : public UObject
{
public:
    BYTE unk_04[0x1a0];
    ULevel *XLevel;
};

class AInfo : public AActor
{
};

class AGameInfo : public AInfo
{
public:
    void execGetNetworkNumber(FFrame &Stack, void *const Result);
    void execParseKillMessage(FFrame &Stack, void *const Result);
};

// AGameInfo::execGetNetworkNumber (RVA 0x129ab0)
void AGameInfo::execGetNetworkNumber(FFrame &Stack, void *const Result)
{
    P_FINISH;
    *(FString *)Result = XLevel->NetDriver
        ? XLevel->NetDriver->LowLevelGetNetworkNumber()
        : FString(GEmptyString);
}

// AGameInfo::execParseKillMessage (RVA 0x129b70)
void AGameInfo::execParseKillMessage(FFrame &Stack, void *const Result)
{
    P_GET_STR(KillerName);
    P_GET_STR(VictimName);
    P_GET_STR(DeathMessage);
    P_FINISH;

    FString OutMsg;
    FString Msg;
    Msg = DeathMessage;

    INT Offset = Msg.InStr(GKillMsgKillerToken);
    if (Offset != -1)
    {
        OutMsg = Msg.Left(Offset);
        OutMsg += KillerName;
        OutMsg += Msg.Right(Msg.Len() - Offset - 2);
        Msg = OutMsg;
    }

    Offset = Msg.InStr(GKillMsgVictimToken);
    if (Offset != -1)
    {
        OutMsg = Msg.Left(Offset);
        OutMsg += VictimName;
        OutMsg += Msg.Right(Msg.Len() - Offset - 2);
    }

    *(FString *)Result = OutMsg;
}

#pragma pack(pop)

// Core string operations used by execParseKillMessage and the script string intrinsics.
// RVA 0x4af0
FString::FString(INT InCount, const TCHAR *InSrc)
    : FArray(InCount ? InCount + 1 : 0, sizeof(TCHAR))
{
    if (ArrayNum)
        appStrncpy((TCHAR *)Data, InSrc, InCount + 1);
}

// RVA 0xf7d0
FString FString::Left(INT Count) const
{
    return FString(Clamp(Count, 0, Len()), **this);
}
