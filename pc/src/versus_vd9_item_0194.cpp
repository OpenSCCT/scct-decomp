// Work item w3_0194: Versus RVA 0xe3610-0xe39c6.
//   0xe3610 UnnamedClass_e3610::MoveMatchToFront   (LTCG: this in EDI, ret 8)
//   0xe3840 UShadowBitmapMaterial::Destroy         (vtable slot 9)
//   0xe38f0 UShadowBitmapMaterial::GetRenderInterface (vtable slot 35, LTCG unit)
//   0xe3950 UnnamedClass_e3950 constructor          (LTCG: this in ESI, owner in ECX)
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;
typedef unsigned __int64 QWORD;
#pragma pack(push, 4)

extern "C" __declspec(dllimport) int __cdecl wcscmp(const TCHAR *A, const TCHAR *B);
extern "C" __declspec(dllimport) TCHAR *__cdecl wcsncpy(TCHAR *D, const TCHAR *S, unsigned int N);
inline INT appStrcmp(const TCHAR *A, const TCHAR *B) { return wcscmp(A, B); }
inline TCHAR *appStrncpy(TCHAR *Dest, const TCHAR *Src, INT MaxLen)
{
    wcsncpy(Dest, Src, MaxLen);
    Dest[MaxLen - 1] = 0;
    return Dest;
}

template<class T> inline T Clamp(T X, T Min, T Max) { return X < Min ? Min : X < Max ? X : Max; }

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline void operator delete(void *Ptr) { GMalloc->Free(Ptr); }
inline void *operator new(unsigned int, void *Mem) { return Mem; }

/*----------------------------------------------------------------------------
    FString (Core/UnTemplate.h).
----------------------------------------------------------------------------*/

class FArray
{
protected:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
public:
    INT Num() const { return ArrayNum; }
};

template<class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

class FString : protected FArray
{
public:
    FString(const FString &Other);                              // 0x4640
    __declspec(noinline) FString(INT InCount, const TCHAR *InSrc); // 0x4af0
    ~FString();                                                 // 0x48b0
    FString &operator=(const FString &Other);                   // 0x4800
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : L""; }
    INT Len() const { return ArrayNum ? ArrayNum - 1 : 0; }
    __declspec(noinline) FString Left(INT Count) const;          // 0xf7d0
    FString Right(INT Count) const;                             // 0x40310
    bool operator==(const TCHAR *Other) const { return appStrcmp(**this, Other) == 0; }
    bool operator==(const FString &Other) const { return appStrcmp(**this, *Other) == 0; }
    static FString Printf(const TCHAR *Fmt, ...);               // 0x11b20
};

/*----------------------------------------------------------------------------
    0xe3610.
----------------------------------------------------------------------------*/

// Neutral name: owner of a TArray<FString> at +0x28 (class not identified).
class UnnamedClass_e3610
{
public:
    BYTE Pad[0x28];
    TArray<FString> Items; // +0x28
    INT MoveMatchToFront(INT Start, INT Number);
};

// RVA 0xe3610. Finds the first entry at or after Start whose two-digit suffix
// (optionally followed by "?ERR") equals Number, swaps it into slot Start and
// returns Start + 1; returns Start when nothing matches.
INT UnnamedClass_e3610::MoveMatchToFront(INT Start, INT Number)
{
    FString Suffix = FString::Printf(L"%02i", Number);
    for (INT i = Start; i < Items.Num(); i++)
    {
        if ((Items(i).Len() > 6 && Items(i).Right(4) == L"?ERR" && Items(i).Left(Items(i).Len() - 4).Right(2) == Suffix)
         || (Items(i).Len() > 2 && Items(i).Right(2) == Suffix))
        {
            if (i == Start)
                return Start + 1;
            FString Temp(Items(i));
            Items(i) = Items(Start);
            Items(Start) = Temp;
            return Start + 1;
        }
    }
    return Start;
}

/*----------------------------------------------------------------------------
    UShadowBitmapMaterial (0xe3840, 0xe38f0).
----------------------------------------------------------------------------*/

// Render device: slot 31 (vtable +0x7c) flushes a cached resource by id.
class URenderDevice
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25(); virtual void Slot26(); virtual void Slot27();
    virtual void Slot28(); virtual void Slot29(); virtual void Slot30();
    virtual void FlushResource(QWORD CacheId);
};

class UClient
{
public:
    BYTE Pad[0x38];
    URenderDevice *RenDev; // +0x38
};

class UEngine
{
public:
    BYTE Pad[0x28];
    UClient *Client; // +0x28
};
extern UEngine *GEngine; // 0x10c9245c

// Render resource owned by the shadow bitmap material (vtable 0x10c0380c).
class FRenderResource
{
public:
    QWORD CacheId; // +0x04
    virtual QWORD GetCacheId();
    ~FRenderResource()
    {
        if (GEngine && GEngine->Client && GEngine->Client->RenDev && CacheId)
            GEngine->Client->RenDev->FlushResource(CacheId);
    }
};

struct FColor
{
    BYTE B, G, R, A;
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA = 255) : B(InB), G(InG), R(InR), A(InA) {}
};

// Solid colour texture (constructed at 0x10a129b0, this in ESI).
class FSolidColorTexture : public FRenderResource
{
public:
    DWORD Pad[2];
    __declspec(noinline) FSolidColorTexture(FColor InColor);
};

extern DWORD GetRenderInterface_Guard;              // was the local static's guard (0x10d506ac)
extern FSolidColorTexture GetRenderInterface_Grey;  // was a local static (0x10d50698)

class UBitmapMaterial
{
public:
    virtual void Destroy();
};

class UShadowBitmapMaterial : public UBitmapMaterial
{
public:
    BYTE Pad[0x60];
    FRenderResource *ShadowTexture;  // +0x64
    FRenderResource *ShadowTexture2; // +0x68
    BYTE Pad2[0x18];
    DWORD Flags;                     // +0x84
    void Destroy();
    virtual FRenderResource *GetRenderInterface();
};

// RVA 0xe3840.
void UShadowBitmapMaterial::Destroy()
{
    if (ShadowTexture) {
        delete ShadowTexture;
        ShadowTexture = 0;
    }
    if (ShadowTexture2) {
        delete ShadowTexture2;
        ShadowTexture2 = 0;
    }
    UBitmapMaterial::Destroy();
}

// RVA 0xe38f0.
FRenderResource *UShadowBitmapMaterial::GetRenderInterface()
{
    if (!(GetRenderInterface_Guard & 1))
    {
        GetRenderInterface_Guard |= 1;
        new(&GetRenderInterface_Grey) FSolidColorTexture(FColor(127, 127, 127, 255));
    }
    if (Flags & 2)
        return &GetRenderInterface_Grey;
    return ShadowTexture;
}

/*----------------------------------------------------------------------------
    0xe3950.
----------------------------------------------------------------------------*/

struct FVector
{
    FLOAT X, Y, Z;
};
struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(const FVector &V, FLOAT InW) { X = V.X; Y = V.Y; Z = V.Z; W = InW; }
};

extern FVector *UnnamedVector_e3950; // global at 0x10ccacc0

class UnnamedOwner_e3950;

// Interface held by the owner at +0x14; slot 5 takes the owner and a plane.
class UnnamedInterface_e3950
{
public:
    virtual void Slot0(); virtual void Slot1(); virtual void Slot2(); virtual void Slot3(); virtual void Slot4();
    virtual void Slot5(UnnamedOwner_e3950 *Owner, DWORD A, DWORD B, DWORD C, DWORD D, FPlane P);
};

class UnnamedOwner_e3950
{
public:
    virtual void Slot0();
    DWORD Pad[4];
    UnnamedInterface_e3950 *Interface; // +0x14
};

// Embedded sub-object at +0x28 (vtable 0x10c04494).
class UnnamedInner_e3950
{
public:
    virtual void Slot0();
};

class UnnamedBase_e3950
{
public:
    virtual void Slot0();
    DWORD A;          // +0x04
    DWORD B;          // +0x08
    DWORD Pad0C;      // +0x0c
    DWORD Kind;       // +0x10
    void *Inner;      // +0x14
    DWORD Pad18;      // +0x18
    DWORD C;          // +0x1c
    DWORD Pad20[2];   // +0x20
    UnnamedBase_e3950() { A = 0; B = 0; C = 0; }
};

// Neutral name: class constructed at 0xe3950 (vtable 0x10c043e8).
class UnnamedClass_e3950 : public UnnamedBase_e3950
{
public:
    UnnamedInner_e3950 InnerObj;   // +0x28
    BYTE Flag;                     // +0x2c
    UnnamedOwner_e3950 *Owner;     // +0x30
    UnnamedClass_e3950(UnnamedOwner_e3950 *InOwner, BYTE InFlag);
    virtual void Slot0();
};

// RVA 0xe3950.
UnnamedClass_e3950::UnnamedClass_e3950(UnnamedOwner_e3950 *InOwner, BYTE InFlag)
{
    Inner = &InnerObj;
    Kind = 5;
    Owner = InOwner;
    Flag = InFlag;
    Owner->Slot0();
    Owner->Interface->Slot5(Owner, 0, 0, 0, 0, FPlane(*UnnamedVector_e3950, 0));
}
#pragma pack(pop)

/*----------------------------------------------------------------------------
    Scaffolding for the LTCG link, not part of the unit. The out-of-line
    callees are defined only so the linker gives them the custom calling
    conventions retail uses; they are separate retail functions.
----------------------------------------------------------------------------*/
void Escape(void *);

FString::FString(INT InCount, const TCHAR *InSrc)
{
    ArrayMax = ArrayNum = InCount ? InCount + 1 : 0;
    Data = ArrayNum ? GMalloc->Malloc(ArrayNum * sizeof(TCHAR), L"FArray") : 0;
    if (ArrayNum)
        appStrncpy((TCHAR *)Data, InSrc, InCount + 1);
}
FString FString::Left(INT Count) const { return FString(Clamp(Count, 0, Len()), **this); }
FSolidColorTexture::FSolidColorTexture(FColor InColor) { Escape(&InColor); Escape(this); }

void Driver_e3610(UnnamedClass_e3610 *O, INT S, INT N) { Escape((void *)O->MoveMatchToFront(S, N)); }
void Driver_e3840(void *Mem) { Escape(&GEngine); Escape(&GMalloc); Escape(new(Mem) UShadowBitmapMaterial); }
void Driver_e38f0(void *Mem) { Escape(&GetRenderInterface_Guard); Escape(new(Mem) UShadowBitmapMaterial); }
void Driver_e3950(void *Mem, UnnamedOwner_e3950 *O, BYTE F) { Escape(&UnnamedVector_e3950); Escape(new(Mem) UnnamedClass_e3950(O, F)); }
