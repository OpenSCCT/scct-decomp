// Work item 0059 (vwork3): Versus RVA 0x981f0, UTexRotator::GetMatrix
// (vtable slot 35 of UTexRotator). Compiled with /GL and linked with /LTCG:
// FRotationMatrix takes this in ESI and the rotator in EDI, the FMatrix
// constructor this in EAX, InZ in EDX, InW in ECX (InX/InY pushed), and
// FMatrix::operator* the result in EAX, this in EDX, Other in ECX.
typedef int INT;
typedef float FLOAT;
typedef unsigned char BYTE;
typedef unsigned long DWORD;

#define PI 3.1415926535897932f

extern "C" __declspec(dllimport) double floor(double);
extern "C" double sin(double);
#pragma intrinsic(sin)

inline INT appTrunc(FLOAT F) { return (INT)F; }
inline INT appFloor(FLOAT F) { return appTrunc((FLOAT)floor(F)); }
inline FLOAT appFractional(FLOAT Value) { return Value - appFloor(Value); }
inline FLOAT appSin(FLOAT Value) { return (FLOAT)sin(Value); }

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) { X = InX; Y = InY; Z = InZ; W = InW; }
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
    FRotator() {}
    FRotator(INT InPitch, INT InYaw, INT InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}
    FRotator operator+(const FRotator &R) const { return FRotator(Pitch + R.Pitch, Yaw + R.Yaw, Roll + R.Roll); }
    FRotator operator*(FLOAT Scale) const { return FRotator(appTrunc(Pitch * Scale), appTrunc(Yaw * Scale), appTrunc(Roll * Scale)); }
    FRotator Clamp() const { return FRotator(Pitch & 65535, Yaw & 65535, Roll & 65535); }
};

struct FMatrix
{
    union
    {
        struct { FPlane XPlane, YPlane, ZPlane, WPlane; };
        FLOAT M[4][4];
    };
    FMatrix() {}
    FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW);
    FMatrix operator*(const FMatrix &Other) const;
};

// RVA 0x4fbc0 (item 0202), copied so LTCG gives it its retail convention.
__declspec(noinline) FMatrix::FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW)
    : XPlane(InX), YPlane(InY), ZPlane(InZ), WPlane(InW)
{
}

// RVA 0x7b110 (item 0299), copied so LTCG gives it its retail convention.
__declspec(noinline) FMatrix FMatrix::operator*(const FMatrix &Other) const
{
    FMatrix Result;
    Result.M[0][0] = M[0][0] * Other.M[0][0] + M[0][1] * Other.M[1][0] + M[0][2] * Other.M[2][0] + M[0][3] * Other.M[3][0];
    Result.M[0][1] = M[0][0] * Other.M[0][1] + M[0][1] * Other.M[1][1] + M[0][2] * Other.M[2][1] + M[0][3] * Other.M[3][1];
    Result.M[0][2] = M[0][0] * Other.M[0][2] + M[0][1] * Other.M[1][2] + M[0][2] * Other.M[2][2] + M[0][3] * Other.M[3][2];
    Result.M[0][3] = M[0][0] * Other.M[0][3] + M[0][1] * Other.M[1][3] + M[0][2] * Other.M[2][3] + M[0][3] * Other.M[3][3];
    Result.M[1][0] = M[1][0] * Other.M[0][0] + M[1][1] * Other.M[1][0] + M[1][2] * Other.M[2][0] + M[1][3] * Other.M[3][0];
    Result.M[1][1] = M[1][0] * Other.M[0][1] + M[1][1] * Other.M[1][1] + M[1][2] * Other.M[2][1] + M[1][3] * Other.M[3][1];
    Result.M[1][2] = M[1][0] * Other.M[0][2] + M[1][1] * Other.M[1][2] + M[1][2] * Other.M[2][2] + M[1][3] * Other.M[3][2];
    Result.M[1][3] = M[1][0] * Other.M[0][3] + M[1][1] * Other.M[1][3] + M[1][2] * Other.M[2][3] + M[1][3] * Other.M[3][3];
    Result.M[2][0] = M[2][0] * Other.M[0][0] + M[2][1] * Other.M[1][0] + M[2][2] * Other.M[2][0] + M[2][3] * Other.M[3][0];
    Result.M[2][1] = M[2][0] * Other.M[0][1] + M[2][1] * Other.M[1][1] + M[2][2] * Other.M[2][1] + M[2][3] * Other.M[3][1];
    Result.M[2][2] = M[2][0] * Other.M[0][2] + M[2][1] * Other.M[1][2] + M[2][2] * Other.M[2][2] + M[2][3] * Other.M[3][2];
    Result.M[2][3] = M[2][0] * Other.M[0][3] + M[2][1] * Other.M[1][3] + M[2][2] * Other.M[2][3] + M[2][3] * Other.M[3][3];
    Result.M[3][0] = M[3][0] * Other.M[0][0] + M[3][1] * Other.M[1][0] + M[3][2] * Other.M[2][0] + M[3][3] * Other.M[3][0];
    Result.M[3][1] = M[3][0] * Other.M[0][1] + M[3][1] * Other.M[1][1] + M[3][2] * Other.M[2][1] + M[3][3] * Other.M[3][1];
    Result.M[3][2] = M[3][0] * Other.M[0][2] + M[3][1] * Other.M[1][2] + M[3][2] * Other.M[2][2] + M[3][3] * Other.M[3][2];
    Result.M[3][3] = M[3][0] * Other.M[0][3] + M[3][1] * Other.M[1][3] + M[3][2] * Other.M[2][3] + M[3][3] * Other.M[3][3];
    return Result;
}

// FGlobalMath at 0x10ccac00; its sine/cosine helper is RVA 0x40950.
struct FGlobalMath
{
    void SinCos(INT Angle, FLOAT *OutSin, FLOAT *OutCos);
};
extern FGlobalMath GMath;

struct FRotationMatrix : public FMatrix
{
    FRotationMatrix(const FRotator &Rot);
};

// RVA 0x81810 (item 0307), copied so LTCG gives it its retail convention.
__declspec(noinline) FRotationMatrix::FRotationMatrix(const FRotator &Rot)
{
    FLOAT SR, SP, SY, CR, CP, CY;
    GMath.SinCos(Rot.Yaw, &SY, &CY);
    GMath.SinCos(Rot.Pitch, &SP, &CP);
    GMath.SinCos(Rot.Roll, &SR, &CR);

    M[0][0] = CP * CY;
    M[0][1] = CP * SY;
    M[0][2] = SP;
    M[0][3] = 0.f;

    M[1][0] = SR * SP * CY - CR * SY;
    M[1][1] = SR * SP * SY + CR * CY;
    M[1][2] = -SR * CP;
    M[1][3] = 0.f;

    M[2][0] = -(CR * SP * CY + SR * SY);
    M[2][1] = CY * SR - CR * SP * SY;
    M[2][2] = CR * CP;
    M[2][3] = 0.f;

    M[3][0] = 0.f;
    M[3][1] = 0.f;
    M[3][2] = 0.f;
    M[3][3] = 1.f;
}

class UMaterial
{
public:
    // Slots 0-25 are not needed here.
    virtual void VSlot00(); virtual void VSlot01(); virtual void VSlot02(); virtual void VSlot03();
    virtual void VSlot04(); virtual void VSlot05(); virtual void VSlot06(); virtual void VSlot07();
    virtual void VSlot08(); virtual void VSlot09(); virtual void VSlot10(); virtual void VSlot11();
    virtual void VSlot12(); virtual void VSlot13(); virtual void VSlot14(); virtual void VSlot15();
    virtual void VSlot16(); virtual void VSlot17(); virtual void VSlot18(); virtual void VSlot19();
    virtual void VSlot20(); virtual void VSlot21(); virtual void VSlot22(); virtual void VSlot23();
    virtual void VSlot24(); virtual void VSlot25();
    virtual INT MaterialUSize();   // slot 26 (+0x68)
    virtual INT MaterialVSize();   // slot 27 (+0x6c)
    BYTE Pad_04[0x54];
};

class UTexModifier : public UMaterial
{
public:
    virtual FMatrix *GetMatrix(FLOAT TimeSeconds);
};

enum ETexRotationType
{
    TR_FixedRotation,
    TR_ConstantlyRotating,
    TR_OscillatingRotation
};

class UTexRotator : public UTexModifier
{
public:
    FMatrix M;                        // +0x58
    BYTE TexRotationType;             // +0x98
    FRotator Rotation;                // +0x9c
    DWORD ConstantRotation : 1;       // +0xa8 (deprecated)
    FLOAT UOffset;                    // +0xac
    FLOAT VOffset;                    // +0xb0
    FRotator OscillationRate;         // +0xb4
    FRotator OscillationAmplitude;    // +0xc0
    FRotator OscillationPhase;        // +0xcc
    virtual FMatrix *GetMatrix(FLOAT TimeSeconds);
};

// RVA 0x981f0
FMatrix *UTexRotator::GetMatrix(FLOAT TimeSeconds)
{
    switch (TexRotationType)
    {
    case TR_ConstantlyRotating:
        M = FRotationMatrix((Rotation * TimeSeconds).Clamp());
        break;
    case TR_OscillatingRotation:
    {
        FLOAT Pitch = OscillationAmplitude.Pitch * appSin(2.f * PI * (appFractional(OscillationRate.Pitch * TimeSeconds / 65535.f) + OscillationPhase.Pitch));
        FLOAT Yaw   = OscillationAmplitude.Yaw   * appSin(2.f * PI * (appFractional(OscillationRate.Yaw   * TimeSeconds / 65535.f) + OscillationPhase.Yaw));
        FLOAT Roll  = OscillationAmplitude.Roll  * appSin(2.f * PI * (appFractional(OscillationRate.Roll  * TimeSeconds / 65535.f) + OscillationPhase.Roll));
        M = FRotationMatrix(Rotation + FRotator(appTrunc(Pitch), appTrunc(Yaw), appTrunc(Roll)));
        break;
    }
    default:
        M = FRotationMatrix(Rotation);
        break;
    }

    if (UOffset != 0.f || VOffset != 0.f)
    {
        FLOAT du = UOffset / MaterialUSize();
        FLOAT dv = VOffset / MaterialVSize();
        M = FMatrix(
                FPlane(1, 0, 0, 0),
                FPlane(0, 1, 0, 0),
                FPlane(-du, -dv, 1, 0),
                FPlane(0, 0, 0, 1)) *
            M *
            FMatrix(
                FPlane(1, 0, 0, 0),
                FPlane(0, 1, 0, 0),
                FPlane(du, dv, 1, 0),
                FPlane(0, 0, 0, 1));
    }
    return &M;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_981f0(UTexRotator *T, FLOAT S) { Escape(&GMath); T->UTexRotator::GetMatrix(S); }
