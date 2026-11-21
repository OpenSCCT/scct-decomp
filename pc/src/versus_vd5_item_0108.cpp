// Work item 0108 (wave 3): Versus RVA 0xb29a0-0xb2d12.
// 0xb29a0 constructor of an unnamed class (vtable 0x10c049fc) that takes a serial id.
// 0xb2a00 / 0xb2a40 range helpers over two floats.
// 0xb2a60 a probe-gated script event with two INT parameters (FName index 0x132).
// 0xb2ab0 SlerpQuat, 0xb2c30 quaternion + origin to FCoords.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned __int64 QWORD;
typedef float FLOAT;

#pragma pack(push, 4) // Unreal packs structures to 4 bytes

template <class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }
template <class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }

extern "C" double __cdecl acos(double);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(acos, sin, sqrt)

#pragma auto_inline(on)
// ---------------------------------------------------------------- 0xb29a0
// Name not recovered; vtable 0x10c049fc.
extern QWORD UnnamedClass_b29a0_NextSerial; // 0x10c96930
class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
};
template <class T> class TArray : public FArray {
public:
    TArray() {}
};
class UnnamedClass_b29a0 {
public:
    TArray<INT> Items; // 0x04 (element type not recovered)
    QWORD Id;   // 0x10
    UnnamedClass_b29a0();
    virtual void VirtualSlot0();
};

#pragma auto_inline(off)
UnnamedClass_b29a0::UnnamedClass_b29a0()
{
    QWORD NewId = UnnamedClass_b29a0_NextSerial++ * 256 + 0xe1;
    Id = NewId;
}

#pragma auto_inline(on)
// ---------------------------------------------------------------- 0xb2a00 / 0xb2a40
struct FRangePair { // name not recovered: two floats
    FLOAT X;
    FLOAT Y;
    FLOAT Size();
    FLOAT GetMin();
};

#pragma auto_inline(off)
FLOAT FRangePair::Size()
{
    return Max(X, Y) - Min(X, Y);
}

#pragma auto_inline(off)
FLOAT FRangePair::GetMin()
{
    return Min(X, Y);
}

#pragma auto_inline(on)
// ---------------------------------------------------------------- 0xb2a60
enum EName { NAME_Unnamed_132 = 0x132 }; // probe event name index; real name not recovered
class FName {
public:
    INT Index;
    FName(EName N) : Index(N) {}
    FName(const FName &Other) : Index(Other.Index) {}
};
class UFunction;
struct FStateFrame {
    void *VfTable;      // FFrame
    void *Node;
    void *Object;
    void *Code;
    void *Locals;
    void *CurrentFrame; // 0x14
    void *StateNode;    // 0x18
    QWORD ProbeMask;    // 0x1c
};
class UObject {
public:
    virtual ~UObject();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
    INT Index;
    UObject *HashNext;
    FStateFrame *StateFrame;
    UFunction *FindFunctionChecked(FName InName, INT Global = 0);
};
class UnnamedClass_b2a60 : public UObject {
public:
    void eventUnnamed_b2a60(INT A, INT B);
};

#pragma auto_inline(off)
void UnnamedClass_b2a60::eventUnnamed_b2a60(INT A, INT B)
{
    if (!StateFrame || (StateFrame->ProbeMask & 0x40)) {
        struct { INT A; INT B; } Parms;
        Parms.A = A;
        Parms.B = B;
        ProcessEvent(FindFunctionChecked(FName(NAME_Unnamed_132)), &Parms);
    }
}

#pragma auto_inline(on)
// ---------------------------------------------------------------- 0xb2ab0
struct FVector { FLOAT X, Y, Z; };
extern const FLOAT SlerpQuat_Delta;  // 0x10c10c14
extern const FLOAT SlerpQuat_Linear; // 0x10c10a68
extern const FLOAT SlerpQuat_Small;  // 0x10c10a08
struct FQuat {
    FLOAT X, Y, Z, W;
    __forceinline void Normalize()
    {
        // Near miss: retail sums ((Z*Z + W*W) + X*X) + Y*Y in a fresh register (12 bytes differ).
        FLOAT SquareSum = (Z * Z + W * W) + (X * X + Y * Y);
        if (SquareSum >= SlerpQuat_Small) { // constant at 0x10c10a08
            FLOAT Scale = 1.0f / (FLOAT)sqrt(SquareSum);
            X *= Scale; Y *= Scale; Z *= Scale; W *= Scale;
        } else {
            X = 0.0f; Y = 0.0f; Z = 0.1f; W = 0.0f;
        }
    }
};
#pragma auto_inline(off)
void SlerpQuat(const FQuat &Quat1, const FQuat &Quat2, FQuat &Result, FLOAT Slerp)
{
    FLOAT Cosom = Quat1.X * Quat2.X + Quat1.Y * Quat2.Y + Quat1.Z * Quat2.Z + Quat1.W * Quat2.W;
    if (Cosom > SlerpQuat_Delta) {
        Result = Quat1;
        return;
    }
    if (Cosom > SlerpQuat_Linear) {
        FLOAT Scale0 = 1.0f - Slerp;
        Result.X = Scale0 * Quat1.X + Slerp * Quat2.X;
        Result.Y = Scale0 * Quat1.Y + Slerp * Quat2.Y;
        Result.Z = Scale0 * Quat1.Z + Slerp * Quat2.Z;
        Result.W = Scale0 * Quat1.W + Slerp * Quat2.W;
    } else {
        FLOAT Omega = acos(Cosom);
        FLOAT SinInv = 1.0f / (FLOAT)sin(Omega);
        FLOAT Scale0 = (FLOAT)sin((1.0f - Slerp) * Omega) * SinInv;
        FLOAT Scale1 = sin(Slerp * Omega) * SinInv;
        Result.X = Scale0 * Quat1.X + Scale1 * Quat2.X;
        Result.Y = Scale0 * Quat1.Y + Scale1 * Quat2.Y;
        Result.Z = Scale0 * Quat1.Z + Scale1 * Quat2.Z;
        Result.W = Scale0 * Quat1.W + Scale1 * Quat2.W;
    }
    Result.Normalize();
}

#pragma auto_inline(on)
// ---------------------------------------------------------------- 0xb2c30
struct FCoords {
    FVector Origin, XAxis, YAxis, ZAxis;
};

#pragma auto_inline(off)
void FQuaternionCoords(const FQuat &Q, const FVector &InOrigin, FCoords &C)
{
    FLOAT x2 = Q.X + Q.X, y2 = Q.Y + Q.Y, z2 = Q.Z + Q.Z;
    FLOAT xx = Q.X * x2, xy = Q.X * y2, xz = Q.X * z2;
    FLOAT yy = Q.Y * y2, yz = Q.Y * z2, zz = Q.Z * z2;
    FLOAT wx = Q.W * x2, wy = Q.W * y2, wz = Q.W * z2;
    C.XAxis.X = 1.0f - (yy + zz);
    C.YAxis.Y = 1.0f - (xx + zz);
    C.ZAxis.Z = 1.0f - (xx + yy);
    C.XAxis.Y = xy - wz;
    C.YAxis.X = xy + wz;
    C.XAxis.Z = xz + wy;
    C.ZAxis.X = xz - wy;
    C.YAxis.Z = yz - wx;
    C.ZAxis.Y = yz + wx;
    C.Origin = InOrigin;
}


#pragma auto_inline(on)
// ---------------------------------------------------------------- scaffolding
#pragma pack(pop)

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
inline void *operator new(unsigned int, void *P) { return P; }
void Driver_b29a0(UnnamedClass_b29a0 *Mem) { Escape(new (Mem) UnnamedClass_b29a0); }
FLOAT Driver_b2a00(FRangePair *R) { return R->Size(); }
FLOAT Driver_b2a40(FRangePair *R) { return R->GetMin(); }
void Driver_b2a60(UnnamedClass_b2a60 *O, INT A, INT B) { O->eventUnnamed_b2a60(A, B); }
void Driver_b2ab0(FQuat *Out, const FQuat *A, const FQuat *B, FLOAT T) { SlerpQuat(*A, *B, *Out, T); }
void Driver_b2c30(FCoords *C, const FQuat *Q, const FVector *O) { FQuaternionCoords(*Q, *O, *C); }
