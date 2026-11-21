// Work item 0336: Versus RVA 0x92710-0x92874.
// AActor::ToLocal / ToWorld (vtable slots 40 and 41), AActor::IsOwnedBy, a
// probe event thunk, and two helpers with neutral names. Most of the unit was
// compiled with /GL and linked with /LTCG (custom register conventions).
typedef unsigned long DWORD;
typedef unsigned __int64 QWORD;
typedef int INT;
typedef float FLOAT;
typedef DWORD UBOOL;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector &operator=(const FVector &V) { X = V.X; Y = V.Y; Z = V.Z; return *this; }
};
struct FRotator { INT Pitch, Yaw, Roll; };

struct FCoords
{
    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;

    FCoords() {}
    FCoords(const FVector &InOrigin, const FVector &InX, const FVector &InY, const FVector &InZ)
        : Origin(InOrigin), XAxis(InX), YAxis(InY), ZAxis(InZ) {}
    FCoords &operator*=(const FCoords &TransformCoords);

    FCoords &operator*=(const FVector &Point) { Origin.X -= Point.X; Origin.Y -= Point.Y; Origin.Z -= Point.Z; return *this; }
    FCoords &operator/=(const FVector &Point) { Origin.X += Point.X; Origin.Y += Point.Y; Origin.Z += Point.Z; return *this; }
    FCoords &operator*=(const FRotator &Rot);
    FCoords &operator/=(const FRotator &Rot);
    FCoords operator*(const FVector &Point) const;
    FCoords operator/(const FVector &Point) const;
    FCoords operator*(const FRotator &Rot) const;
    FCoords operator/(const FRotator &Rot) const;
};

struct FGlobalMath
{
    FVector WorldMin;
    FVector WorldMax;
    FCoords UnitCoords;
    void SinCos(INT Angle, FLOAT *S, FLOAT *C) const;   // RVA 0x40950
};
extern FGlobalMath GMath;
// Pointers next to GMath (0x10ccacb8..0x10ccacc4) to the shared unit axes and
// the zero vector.
extern FVector *GMath_XAxisVector;
extern FVector *GMath_YAxisVector;
extern FVector *GMath_ZAxisVector;
extern FVector *UnnamedRecord_927b0_DefaultVector;   // the zero vector

// RVA 0x40d90 (another unit; defined so LTCG gives it the same convention).
inline FCoords &FCoords::operator*=(const FRotator &Rot)
{
    FLOAT S, C;
    GMath.SinCos(Rot.Yaw, &S, &C);
    *this *= FCoords(*UnnamedRecord_927b0_DefaultVector, FVector(C, S, 0.f), FVector(-S, C, 0.f), *GMath_ZAxisVector);
    GMath.SinCos(Rot.Pitch, &S, &C);
    *this *= FCoords(*UnnamedRecord_927b0_DefaultVector, FVector(C, 0.f, S), *GMath_YAxisVector, FVector(-S, 0.f, C));
    GMath.SinCos(Rot.Roll, &S, &C);
    *this *= FCoords(*UnnamedRecord_927b0_DefaultVector, *GMath_XAxisVector, FVector(0.f, C, -S), FVector(0.f, S, C));
    return *this;
}


// RVA 0x862a0 (another unit; defined here so LTCG gives it the same register convention).
inline FCoords FCoords::operator*(const FVector &Point) const { return FCoords(*this) *= Point; }
// RVA 0x7c470 (another unit).
inline FCoords FCoords::operator/(const FVector &Point) const { return FCoords(*this) /= Point; }
// RVA 0x40f40 (another unit).
inline FCoords FCoords::operator*(const FRotator &Rot) const { return FCoords(*this) *= Rot; }



// RVA 0x92810: a script event thunk guarded by an inlined UObject::IsProbing.
// Event name index 0x12f (NAME_PROBEMIN is 0x12c, so probe bit 3).
struct FName
{
    INT Index;
    FName(INT InIndex) : Index(InIndex) {}
    FName(const FName &Other) : Index(Other.Index) {}
    INT GetIndex() const { return Index; }
};
enum { NAME_PROBEMIN = 0x12c, NAME_PROBEMAX = 0x16c };
struct UFunction;
#pragma pack(push, 4)
struct FStateFrame
{
    unsigned char Pad[0x1c];
    QWORD ProbeMask;        // 0x1c
};
#pragma pack(pop)
struct UObject
{
    virtual void QueryInterface();
    virtual void AddRef();
    virtual void Release();
    virtual ~UObject();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);

    DWORD Index;            // 0x04
    UObject *HashNext;      // 0x08
    FStateFrame *StateFrame; // 0x0c

    UFunction *FindFunctionChecked(FName InName, INT Global = 0);
    UBOOL IsProbing(FName ProbeName)
    {
        return (ProbeName.GetIndex() < NAME_PROBEMIN)
            || (ProbeName.GetIndex() >= NAME_PROBEMAX)
            || (!StateFrame)
            || (StateFrame->ProbeMask & ((QWORD)1 << (ProbeName.GetIndex() - NAME_PROBEMIN)));
    }
};
struct AActor : UObject
{
    unsigned char Pad10[0x70];
    FVector Location;          // 0x80
    unsigned char Pad8C[0x54];
    FRotator Rotation;         // 0xe0
    unsigned char PadEC[0x18];
    AActor *Owner;             // 0x104

    virtual FCoords ToLocal() const;   // vtable slot 40
    virtual FCoords ToWorld() const;   // vtable slot 41
    UBOOL IsOwnedBy(const AActor *TestOwner) const;
};

// RVA 0x92710 (vtable slot 40)
FCoords AActor::ToLocal() const
{
    return GMath.UnitCoords / Rotation / Location;
}

// RVA 0x92750 (vtable slot 41)
FCoords AActor::ToWorld() const
{
    return GMath.UnitCoords * Location * Rotation;
}

// RVA 0x92790
__declspec(noinline) UBOOL AActor::IsOwnedBy(const AActor *TestOwner) const
{
    for (const AActor *Arg = this; Arg; Arg = Arg->Owner)
        if (Arg == TestOwner)
            return 1;
    return 0;
}

// RVA 0x927b0. Neutral names: a 0x38-byte record initialised from two
// arguments and two copies of the zero vector reached through a global pointer.
struct UnnamedRecord_927b0
{
    DWORD Key;          // 0x00
    DWORD Field04;
    FVector VectorA;    // 0x08
    FVector VectorB;    // 0x14
    DWORD Field20;
    DWORD Value;        // 0x24
    INT Field28;
    DWORD Field2C;
    DWORD Field30;
    DWORD Field34;

    UnnamedRecord_927b0(DWORD InValue, DWORD InKey);
};

UnnamedRecord_927b0::UnnamedRecord_927b0(DWORD InValue, DWORD InKey)
{
    Key = InKey;
    Field04 = 0;
    VectorA = *UnnamedRecord_927b0_DefaultVector;
    VectorB = *UnnamedRecord_927b0_DefaultVector;
    Field20 = 0;
    Value = InValue;
    Field28 = -1;
    Field2C = 0;
    Field34 = 0;
}

struct UnnamedEvent_92810_Parms
{
    DWORD Arg;
};
struct UnnamedClass_92810 : UObject
{
    void eventUnnamed_92810(DWORD Arg);
};
__declspec(noinline) void UnnamedClass_92810::eventUnnamed_92810(DWORD Arg)
{
    if (IsProbing(FName(0x12f)))
    {
        UnnamedEvent_92810_Parms Parms;
        Parms.Arg = Arg;
        ProcessEvent(FindFunctionChecked(FName(0x12f)), &Parms);
    }
}

// RVA 0x92850. Neutral names: looks up a 16-byte entry by index in an array
// held by a sub-object, falling back to a default when out of range or empty.
struct UnnamedEntry_92850 { void *Value; DWORD Pad[3]; };
struct UnnamedTable_92850
{
    unsigned char Pad[0x114];
    UnnamedEntry_92850 *Data;   // 0x114
    INT Num;                    // 0x118
};
struct UnnamedOwner_92850
{
    unsigned char Pad[0x2c];
    void **Default;             // 0x2c
    unsigned char Pad30[0x10c];
    UnnamedTable_92850 *Table;  // 0x13c

    void *GetEntry(INT Index) const;
};
__declspec(noinline) void *UnnamedOwner_92850::GetEntry(INT Index) const
{
    void *Value;
    if (Index < Table->Num && (Value = Table->Data[Index].Value) != 0)
        return Value;
    return *Default;
}

// ---------------------------------------------------------------------------
// Scaffolding for the LTCG link, not part of the unit (roots: Driver_92710,
// Driver_92750, Driver_92790, Driver_92810, Driver_92850).
// __declspec(noinline) above stands in for retail call sites the LTCG inliner declined.
inline void *operator new(unsigned int, void *Where) { return Where; }
void Escape(void *);
void Driver_927b0(void *Mem, DWORD A, DWORD B)
{
    Escape(&UnnamedRecord_927b0_DefaultVector);
    new (Mem) UnnamedRecord_927b0(A, B);
    Escape(Mem);
    new ((char *)Mem + 0x40) UnnamedRecord_927b0(B, A);
    Escape(Mem);
    new ((char *)Mem + 0x80) UnnamedRecord_927b0(A, 7);
    Escape(Mem);
    new ((char *)Mem + 0xc0) UnnamedRecord_927b0(3, A);
}
void Driver_92710(const AActor *A, FCoords *Out)
{
    Escape(&GMath);
    Escape(new (Out) AActor);
    Out[0] = A->AActor::ToLocal();
    Escape(Out);
    Out[1] = A->AActor::ToLocal();
}
void Driver_92750(const AActor *A, FCoords *Out)
{
    Escape(&GMath);
    Escape(new (Out) AActor);
    Out[0] = A->AActor::ToWorld();
    Escape(Out);
    Out[1] = A->AActor::ToWorld();
}
UBOOL Driver_92790(const AActor **A, INT N)
{
    UBOOL R = 0;
    if (A[0]->IsOwnedBy(A[1])) Escape((void *)A[2]);
    if (A[1]->IsOwnedBy(A[2])) Escape((void *)A[3]);
    if (A[2]->IsOwnedBy(A[3])) Escape((void *)A[4]);
    if (A[3]->IsOwnedBy(A[4])) Escape((void *)A[5]);
    if (A[4]->IsOwnedBy(A[5])) Escape((void *)A[6]);
    if (A[5]->IsOwnedBy(A[6])) Escape((void *)A[7]);
    if (A[6]->IsOwnedBy(A[7])) Escape((void *)A[8]);
    if (A[7]->IsOwnedBy(A[8])) Escape((void *)A[9]);
    if (A[8]->IsOwnedBy(A[9])) Escape((void *)A[10]);
    if (A[9]->IsOwnedBy(A[10])) Escape((void *)A[11]);
    if (A[10]->IsOwnedBy(A[11])) Escape((void *)A[12]);
    if (A[11]->IsOwnedBy(A[12])) Escape((void *)A[13]);
    if (A[12]->IsOwnedBy(A[13])) Escape((void *)A[14]);
    if (A[13]->IsOwnedBy(A[14])) Escape((void *)A[15]);
    if (A[14]->IsOwnedBy(A[15])) Escape((void *)A[16]);
    if (A[15]->IsOwnedBy(A[16])) Escape((void *)A[17]);
    if (A[16]->IsOwnedBy(A[17])) Escape((void *)A[18]);
    if (A[17]->IsOwnedBy(A[18])) Escape((void *)A[19]);
    if (A[18]->IsOwnedBy(A[19])) Escape((void *)A[20]);
    if (A[19]->IsOwnedBy(A[20])) Escape((void *)A[21]);
    if (A[20]->IsOwnedBy(A[21])) Escape((void *)A[22]);
    if (A[21]->IsOwnedBy(A[22])) Escape((void *)A[23]);
    if (A[22]->IsOwnedBy(A[23])) Escape((void *)A[24]);
    if (A[23]->IsOwnedBy(A[24])) Escape((void *)A[25]);
    return R;
}
void Driver_92810(UnnamedClass_92810 *A, UnnamedClass_92810 *B, DWORD X)
{
    A->eventUnnamed_92810(X);
    B->eventUnnamed_92810(X + 1);
    A->eventUnnamed_92810(5);
}
void *Driver_92850(const UnnamedOwner_92850 *A, const UnnamedOwner_92850 *B, INT I)
{
    Escape(A->GetEntry(I));
    Escape(B->GetEntry(I + 1));
    return A->GetEntry(3);
}
