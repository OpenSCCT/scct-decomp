// Work item 0391: Versus RVA 0x11de70-0x11e460 (1520 bytes).
// FDynamicLight::Update (Unreal Engine 2 UnLight.cpp), compiled with VC7.0 /GL
// and linked with /LTCG (this in EDI).

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;

#define PI (3.1415926535897932f)

extern "C" double __cdecl sin(double);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sin, sqrt)

inline FLOAT appSin(FLOAT Value) { return (FLOAT)sin(Value); }
inline FLOAT appSqrt(FLOAT Value) { return (FLOAT)sqrt(Value); }

FLOAT appFrand();           // 0x1090f430
INT appFloor(FLOAT F);      // 0x1090f4b0

template<class T> T Min(const T A, const T B); // 0x1090c880
template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }
template<class T> inline T Clamp(const T X, const T InMin, const T InMax)
{
    return X < InMin ? InMin : X < InMax ? X : InMax;
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
    FVector SafeNormal() const;     // 0x10950d30
    FVector UnsafeNormal() const;   // 0x109407e0
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
    FPlane(const FVector &V, FLOAT InW) : FVector(V), W(InW) {}
    FPlane operator*(FLOAT Scale) const { return FPlane(X * Scale, Y * Scale, Z * Scale, W * Scale); }
};

struct FColor
{
    BYTE B, G, R, A;
    FLOAT Brightness() const;       // 0x10a218e0
};

struct FRotator;

struct FCoords
{
    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;
    FCoords operator/(const FRotator &Rot) const; // 0x109411a0
};

struct FGlobalMath
{
    FCoords UnitCoords;
};
extern FGlobalMath GMath;           // 0x10ccac00

struct FRotator
{
    INT Pitch, Yaw, Roll;
    inline FVector Vector() const { return (GMath.UnitCoords / *this).XAxis; }
};

template<class T> class TArray
{
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    T &operator()(INT i) { return Data[i]; }
    INT Num() const { return ArrayNum; }
};

class UClass;

class UObject
{
public:
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0c();
    virtual void V10(); virtual void V14(); virtual void V18(); virtual void V1c();
    virtual void V20(); virtual void V24(); virtual void V28(); virtual void V2c();
    virtual void V30(); virtual void V34(); virtual void V38(); virtual void V3c();
    virtual void V40(); virtual void V44(); virtual void V48(); virtual void V4c();
    virtual void V50(); virtual void V54(); virtual void V58(); virtual void V5c();
    virtual void V60(); virtual void V64(); virtual void V68(); virtual void V6c();
    virtual FLOAT WorldLightRadius() const; // vtable +0x70

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
public:
    BYTE Pad30[0xac - 0x30];
    TArray<BYTE> Defaults;          // 0xac
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = (UClass *)TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return 0;
}

class UPalette : public UObject
{
public:
    TArray<FColor> Colors;          // 0x28
};

class UMaterial : public UObject
{
};

class UTexture : public UMaterial
{
public:
    BYTE Pad28[0x9c - 0x28];
    UPalette *Palette;              // 0x9c
    static UClass PrivateStaticClass; // 0x10cbd8c8
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

template<class T> T *Cast(UObject *Src); // 0x10974810

class ALevelInfo : public UObject
{
public:
    BYTE Pad28[0x3b0 - 0x28];
    FLOAT TimeSeconds;              // 0x3b0
    BYTE Pad3b4[0x484 - 0x3b4];
    FLOAT Brightness;               // 0x484
};

class AActor : public UObject
{
public:
    BYTE Pad28[0x80 - 0x28];
    FVector Location;               // 0x80
    BYTE Pad8c[0xe0 - 0x8c];
    FRotator Rotation;              // 0xe0
    BYTE Padec[0xf8 - 0xec];
    FLOAT LightBrightness;          // 0xf8
    BYTE Padfc[0x134 - 0xfc];
    INT LightRevision;              // 0x134 (neutral name)
    BYTE Pad138[0x1a0 - 0x138];
    ALevelInfo *Level;              // 0x1a0
    BYTE Pad1a4[0x1a8 - 0x1a4];
    FLOAT LifeSpan;                 // 0x1a8
    BYTE Pad1ac[0x240 - 0x1ac];
    TArray<UMaterial *> Skins;      // 0x240
    BYTE Pad24c[0x2d1 - 0x24c];
    BYTE LightType;                 // 0x2d1
    BYTE LightEffect;               // 0x2d2
    BYTE LightHue;                  // 0x2d3
    BYTE LightSaturation;           // 0x2d4
    BYTE LightPeriod;               // 0x2d5
    BYTE LightPhase;                // 0x2d6
    BYTE Pad2d7[0x2e8 - 0x2d7];
    DWORD Bits2e8_0 : 8;            // 0x2e8 bits 0..7
    DWORD bLightFlag8 : 1;          // 0x2e8 bit 8 (0x100, neutral name)
    DWORD Bits2e8_9 : 6;            // 0x2e8 bits 9..14
    DWORD bLightFlag15 : 1;         // 0x2e8 bit 15 (0x8000, neutral name)
    DWORD Bits2e8_16 : 1;           // 0x2e8 bit 16
    DWORD bDynamicLight : 1;        // 0x2e8 bit 17 (0x20000)
    DWORD Bits2e8_18 : 14;          // 0x2e8 bits 18..31

    FLOAT LifeFraction();           // 0x10a21920
};

enum ELightType
{
    LT_None               = 0,
    LT_Steady             = 1,
    LT_Pulse              = 2,
    LT_Blink              = 3,
    LT_Flicker            = 4,
    LT_Strobe             = 5,
    LT_BackdropLight      = 6,
    LT_SubtlePulse        = 7,
    LT_TexturePaletteOnce = 8,
    LT_TexturePaletteLoop = 9,
    LT_FadeOut            = 10,
};

enum ELightEffect
{
    LE_None          = 0,
    LE_StaticSpot    = 8,
    LE_Spotlight     = 12,
    LE_Sunlight      = 19,
    LE_CustomSpot_22 = 22,          // 0x16 (neutral name)
};

FPlane FGetHSV(BYTE H, BYTE S, BYTE V); // 0x109f22d0

// Local statics in FDynamicLight::Update (LT_Strobe case)
extern FLOAT FDynamicLight_Update_LastUpdateTime; // 0x10ccad2c
extern INT FDynamicLight_Update_Toggle;           // 0x10ccad28

class FDynamicLight
{
public:
    AActor *Actor;                  // 0x00
    INT Revision;                   // 0x04
    FPlane Color;                   // 0x08
    FVector Position;               // 0x18
    FVector Direction;              // 0x24
    FLOAT Radius;                   // 0x30
    DWORD Dynamic : 1;              // 0x34 bit 0
    DWORD Changed : 1;              // 0x34 bit 1
    DWORD FlagRest : 30;
    INT Pad38;                      // 0x38
    FLOAT Alpha;                    // 0x3c

    void Update();
};

// RVA 0x11de70
void FDynamicLight::Update()
{
    if (!Actor)
        return;

    FPlane BaseColor = FGetHSV(Actor->LightHue, Actor->LightSaturation, 255);
    FLOAT Intensity = 0.0f;

    if (Actor->LightType == LT_Steady)
        Intensity = 1.0f;
    else if (Actor->LightType == LT_Pulse)
        Intensity = 0.6f + 0.39f * appSin(Actor->Level->TimeSeconds * 35.0f * 2.0f * PI / Max((INT)Actor->LightPeriod, 1) + (Actor->LightPhase << 8));
    else if (Actor->LightType == LT_Blink)
    {
        if ((INT)((Actor->Level->TimeSeconds * 35.0f * 65536.0f) / (FLOAT)(Actor->LightPeriod + 1) + (Actor->LightPhase << 8)) & 1)
            Intensity = 0.0f;
        else
            Intensity = 1.0f;
    }
    else if (Actor->LightType == LT_Flicker)
    {
        FLOAT Rand = appFrand();
        Intensity = Rand < 0.5f ? 0.0f : Rand;
    }
    else if (Actor->LightType == LT_Strobe)
    {
        if (FDynamicLight_Update_LastUpdateTime != Actor->Level->TimeSeconds)
        {
            FDynamicLight_Update_LastUpdateTime = Actor->Level->TimeSeconds;
            FDynamicLight_Update_Toggle ^= 1;
        }
        Intensity = FDynamicLight_Update_Toggle ? 0.0f : 1.0f;
    }
    else if (Actor->LightType == LT_SubtlePulse)
        Intensity = 0.9f + 0.09f * appSin(Actor->Level->TimeSeconds * 35.0f * 2.0f * PI / Max((INT)Actor->LightPeriod, 1) + (Actor->LightPhase << 8));
    else if (Actor->LightType == LT_TexturePaletteOnce)
    {
        if (Actor->Skins.Num())
        {
            UTexture *Texture = Cast<UTexture>(Actor->Skins(0));
            if (Texture && Texture->Palette)
            {
                FColor C = Texture->Palette->Colors(appFloor(255.0f * Actor->LifeFraction()));
                BaseColor = FPlane(FVector(C.R, C.G, C.B).SafeNormal(), 0.0f);
                Intensity = C.Brightness() * 2.8f;
            }
        }
    }
    else if (Actor->LightType == LT_TexturePaletteLoop)
    {
        if (Actor->Skins.Num())
        {
            UTexture *Texture = Cast<UTexture>(Actor->Skins(0));
            if (Texture && Texture->Palette)
            {
                FColor C = Texture->Palette->Colors(((INT)((Actor->Level->TimeSeconds * 35.0f / Max((INT)Actor->LightPeriod, 1) + Actor->LightPhase) * 256.0f) & 255) % 255);
                BaseColor = FPlane(FVector(C.R, C.G, C.B).UnsafeNormal(), 0.0f);
                Intensity = C.Brightness() * 2.8f;
            }
        }
        Dynamic = 1;
    }
    else if (Actor->LightType == LT_FadeOut)
        Intensity = Min(1.0f, (1.0f - Actor->LifeFraction()) * 1.5f);

    Color = BaseColor * (Actor->LightBrightness * (0.5f / 255.0f)) * Intensity * Actor->Level->Brightness;

    if (Actor->LightEffect == LE_Sunlight)
    {
        Direction = Actor->Rotation.Vector();
    }
    else if (Actor->LightEffect == LE_Spotlight || Actor->LightEffect == LE_StaticSpot || Actor->LightEffect == LE_CustomSpot_22)
    {
        Position = Actor->Location;
        Direction = Actor->Rotation.Vector();
        Radius = Actor->WorldLightRadius();
    }
    else
    {
        Position = Actor->Location;
        Radius = Actor->WorldLightRadius();
    }

    Alpha = 1.0f;
    Dynamic = Actor->bDynamicLight || Actor->LightEffect == LE_CustomSpot_22;
    Changed = !Dynamic && (Actor->bLightFlag8 || Actor->bLightFlag15);
    Revision = Actor->LightRevision;
}

// ============================================================================
// Scaffolding for the LTCG link, not part of the unit.
// Reproduces LTCG callee definitions so LINK /LTCG assigns retail register
// conventions across calls.
// ============================================================================
template<class T, class U> inline T Lerp(const T &A, const T &B, const U &Alpha)
{
    return A + (B - A) * Alpha;
}
extern FVector *GHSVWhite;

__declspec(noinline) FPlane FGetHSV(BYTE H, BYTE S, BYTE V)
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

template<class T> __declspec(noinline) T *Cast(UObject *Src)
{
    return Src && Src->IsA(T::StaticClass()) ? (T *)Src : 0;
}

__declspec(noinline) FLOAT AActor::LifeFraction()
{
    return Clamp(1.f - LifeSpan / ((AActor *)Class->Defaults.Data)->LifeSpan, 0.f, 1.f);
}

__declspec(noinline) FVector FVector::SafeNormal() const
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum < 1.e-8f)
        return FVector(0.f, 0.f, 0.f);
    FLOAT Scale = 1.f / appSqrt(SquareSum);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}

__declspec(noinline) FVector FVector::UnsafeNormal() const
{
    FLOAT Scale = 1.f / appSqrt(X * X + Y * Y + Z * Z);
    return FVector(X * Scale, Y * Scale, Z * Scale);
}

__declspec(noinline) FLOAT FColor::Brightness() const
{
    return (2.f * R + 3.f * G + B) / (6.f * 256.f);
}

void Escape(void *);
void UseVec(const FVector &);

void Driver_11de70(FDynamicLight *L, AActor *A, BYTE H, BYTE S, BYTE V, FVector *V1, FVector *V2)
{
    Escape(&GMath);
    Escape(&GHSVWhite);
    Escape(&FDynamicLight_Update_LastUpdateTime);
    Escape(&FDynamicLight_Update_Toggle);
    L->Actor = A;
    L->Revision = -1;
    L->Update();
    L->Update();
    FPlane LocalP = FGetHSV(H, S, V);
    Escape(&LocalP);
    UseVec(V1->SafeNormal());
    UseVec(V2->UnsafeNormal());
    Escape(L);
}
