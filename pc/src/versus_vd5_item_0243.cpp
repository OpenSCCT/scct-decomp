// Work item 0243: Versus RVA 0xf21d0-0xf248c.
// AGameStats script natives (execGetMapFileName, execGetStatsIdentifier) and
// FGetHSV from UnMath (hue/saturation/brightness to FPlane colour). The object
// was built with /GL and linked with /LTCG: FString::operator=(const TCHAR*)
// takes `this` in ESI and the string in EDI, FGetHSV takes H in AL, S in DL,
// V on the stack and the return pointer in ECX.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
inline FLOAT appSqrt(FLOAT A) { return (FLOAT)sqrt(A); }

template<class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

class __single_inheritance UObject;
class UClass;

class FString
{
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString &operator=(const FString &Other);   // 0x4800
    FString &operator=(const TCHAR *Other);     // 0x4750
};

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
extern "C" void *__cdecl appMemcpy(void *Dest, const void *Src, INT Count);
class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

// RVA 0x4750 (published separately); defined here so the LTCG link gives
// it retail's ESI/EDI convention.
FString &FString::operator=(const TCHAR *Other)
{
    if (Other != Data) {
        if (*Other == 0) {
            if (Data) {
                ArrayNum = 0;
                ArrayMax = 0;
                GMalloc->Free(Data);
                Data = 0;
            }
        } else {
            if (Data == 0) {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Malloc(ArrayMax * sizeof(TCHAR), L"FString::=");
            } else {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR *)GMalloc->Realloc(Data, ArrayMax * sizeof(TCHAR), L"FArray");
            }
            appMemcpy(Data, Other, ArrayNum * sizeof(TCHAR));
        }
    }
    return *this;
}

struct FFrame
{
    void *VfTable;
    void *Node;
    UObject *Object;
    BYTE *Code;
    inline void Step(UObject *Context, void *Result);
};

typedef void (UObject::*Native)(FFrame &Stack, void *Result);
extern Native GNatives[];   // 0x10c819d8

inline void FFrame::Step(UObject *Context, void *Result)
{
    INT B = *Code++;
    (Context->*GNatives[B])(*this, Result);
}

class UObject
{
public:
    virtual ~UObject();
    INT Index;
    void *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    INT Name;
    UClass *Class;
    inline UBOOL IsA(UClass *SomeBase) const;
};

class UField : public UObject
{
public:
    UField *SuperField;
    UField *Next;
};

class UClass : public UField
{
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = (UClass *)TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return 0;
}

template<class T> inline T *Cast(UObject *Src)
{
    return Src && Src->IsA(T::StaticClass()) ? (T *)Src : 0;
}

#define P_GET_OBJECT(cls, var) cls *var = 0; Stack.Step(Stack.Object, &var);
#define P_FINISH Stack.Code++;

// Neutral names: classes identified only by their PrivateStaticClass addresses.
class UnnamedClass_cbc5e8 : public UObject
{
public:
    static UClass PrivateStaticClass;   // 0x10cbc5e8
    static UClass *StaticClass() { return &PrivateStaticClass; }
};
class UnnamedClass_cbc930 : public UObject
{
public:
    static UClass PrivateStaticClass;   // 0x10cbc930
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

class APlayerController : public UObject
{
public:
    BYTE Pad[0x4a4 - 0x28];
    UObject *Player;   // 0x4a4
    static UClass PrivateStaticClass;   // 0x10cc6ce8
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

class ALevelInfo : public UObject
{
public:
    BYTE Pad[0x110 - 0x28];
    FString MapFileName;   // 0x110 (neutral name)
};

class AGameStats : public UObject
{
public:
    BYTE Pad[0x1a4 - 0x28];
    ALevelInfo *Level;   // 0x1a4
    void execGetMapFileName(FFrame &Stack, void *Result);
    void execGetStatsIdentifier(FFrame &Stack, void *Result);
};

extern const TCHAR EmptyString[];   // L"" at 0x10c494b8

// RVA 0xf21d0
void AGameStats::execGetMapFileName(FFrame &Stack, void *Result)
{
    P_FINISH;
    *(FString *)Result = Level->MapFileName;
}

// RVA 0xf21f0. The online branches were compiled out of the PC build.
void AGameStats::execGetStatsIdentifier(FFrame &Stack, void *Result)
{
    P_GET_OBJECT(UObject, Obj);
    P_FINISH;
    APlayerController *PC = Cast<APlayerController>(Obj);
    if (PC && (Cast<UnnamedClass_cbc5e8>(PC->Player) || Cast<UnnamedClass_cbc930>(PC->Player)))
        return;
    *(FString *)Result = EmptyString;
}

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FVector V, FLOAT InW) : FVector(V), W(InW) {}
};

template<class T, class U> inline T Lerp(const T &A, const T &B, const U &Alpha)
{
    return A + (B - A) * Alpha;
}

extern FVector *GHSVWhite;   // 0x10ccabf8, neutral name

// RVA 0xf22d0
FPlane FGetHSV(BYTE H, BYTE S, BYTE V)
{
    FLOAT FH = H;
    FLOAT FS = S;
    FLOAT Brightness = V * (1.4f / 255.f);
    Brightness = Brightness / (0.01f + appSqrt(Brightness)) * 0.7f;
    Brightness = Clamp(Brightness, 0.f, 1.f);
    FVector Hue = (FH < 86.f) ? FVector((85.f - FH) * (1.f / 85.f), FH * (1.f / 85.f), 0.f)
                : (FH < 171.f) ? FVector(0.f, (170.f - FH) * (1.f / 85.f), (FH - 85.f) * (1.f / 85.f))
                : FVector((FH - 170.f) * (1.f / 85.f), 0.f, (255.f - FH) * (1.f / 84.f));
    return FPlane(Lerp(Hue, *GHSVWhite, FS * (1.f / 255.f)) * Brightness, 1.f);
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
extern Native GExecTable[2];
void Driver_f21d0() { GExecTable[0] = (Native)&AGameStats::execGetMapFileName; }
void Driver_f21f0() { Escape(GNatives); Escape(&GMalloc); GExecTable[1] = (Native)&AGameStats::execGetStatsIdentifier; }
void Driver_f22d0(FPlane *Out, BYTE H, BYTE S, BYTE V) { Escape(&GHSVWhite); *Out = FGetHSV(H, S, V); }
