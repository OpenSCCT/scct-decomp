// Work item 0126 (w3): Versus RVA 0xb7f30-0xb84fc. Skeletal-animation code
// near USkeletalMeshInstance (vtable 0x30a048). Field names are neutral where
// nothing identifies them.
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;

struct FRotator {
    INT Pitch, Yaw, Roll;
};

inline FRotator MakeRotator(INT Pitch, INT Yaw, INT Roll)
{
    FRotator R;
    R.Roll = Roll; R.Pitch = Pitch; R.Yaw = Yaw;
    return R;
}

struct UnnamedResult_b7f30 {
    char Pad[0x48];
    INT Value48;
};

struct UnnamedChannelOwner_b7f30 {
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual UnnamedResult_b7f30 *Find(INT Key);   // slot 24 (+0x60)
};

struct UnnamedChannelEntry_b7f30 {           // 0x18 bytes
    UnnamedChannelOwner_b7f30 *Owner;
    INT Pad[5];
};

struct UnnamedSettings_b7f30 {
    INT Pad0;
    INT Index;          // +0x04
    INT Key;            // +0x08
    char Pad0c[0x74 - 0x0c];
    unsigned char bInvert; // +0x74
};

// Neutral name: the owner of the rotation tracking fields.
struct UnnamedRotTracker_b7f30 {
    char Pad0[0xa8];
    UnnamedChannelEntry_b7f30 *Channels;     // +0xa8
    char PadAc[0x100 - 0xac];
    UnnamedSettings_b7f30 *Settings;         // +0x100
    char Pad104[0x194 - 0x104];
    FRotator Current;                        // +0x194
    char Pad1a0[0x1ac - 0x1a0];
    FRotator Previous;                       // +0x1ac

    FRotator ConsumeYawDelta();
};

FRotator UnnamedRotTracker_b7f30::ConsumeYawDelta()
{
    INT Delta = Previous.Yaw - Current.Yaw;
    Previous = Current;
    UnnamedChannelOwner_b7f30 *Owner = Channels[Settings->Index].Owner;
    UnnamedResult_b7f30 *R;
    if (Owner && (R = Owner->Find(Settings->Key)) != 0 && R->Value48 == 0) {
        if (Settings->bInvert)
            Delta = -Delta;
    } else if (!Settings->bInvert) {
        Delta = -Delta;
    }
    return MakeRotator(0, Delta, 0);
}


// ---------------------------------------------------------------------------
// RVA 0xb8100: fills Out with one (Origin, Direction) pair per bone of a
// skeletal mesh instance. LTCG: Out in EBX, the other arguments pushed.
struct FVector {
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FVector operator*(const FVector &V) const { return FVector(X * V.X, Y * V.Y, Z * V.Z); }
    FVector &operator-=(const FVector &V) { X -= V.X; Y -= V.Y; Z -= V.Z; return *this; }
    UBOOL Normalize();                     // RVA 0x4f7a0
};

// Imported data at 0x10ccacc4 (neutral name; also the start value of FBox::Min).
__declspec(dllimport) extern const FVector GBoxStartMin;

template<class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }

struct FCoords { FVector Origin, XAxis, YAxis, ZAxis; };

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const unsigned short *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const unsigned short *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArray {
public:
    INT Add(INT Count, INT ElementSize);    // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack); // RVA 0x4550
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray {
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Reset()
    {
        ArrayNum = 0;
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
            ArrayMax = 0;
        }
    }
};


struct FMeshBone {                      // 0x40 bytes
    char Pad0[0x34];
    INT ParentIndex;                    // +0x34
    INT Pad38[2];
};

struct USkeletalMesh_b8100 {
    char Pad0[0x19c];
    FMeshBone *RefSkeleton;             // +0x19c
    INT RefSkeletonNum;                 // +0x1a0
    char Pad1a4[0x1b0 - 0x1a4];
    INT HasSkeleton;                    // +0x1b0
};

class USkeletalMeshInstance_b8100 {
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29(); virtual void V30(); virtual void V31();
    virtual USkeletalMesh_b8100 *GetMesh();                       // slot 32 (+0x80)
    virtual void V33(); virtual void V34(); virtual void V35();
    virtual void V36(); virtual void V37(); virtual void V38(); virtual void V39();
    virtual void V40(); virtual void V41(); virtual void V42(); virtual void V43();
    virtual void V44(); virtual void V45(); virtual void V46(); virtual void V47();
    virtual void V48(); virtual void V49(); virtual void V50(); virtual void V51();
    virtual void V52(); virtual void V53(); virtual void V54(); virtual void V55();
    virtual void V56(); virtual void V57(); virtual void V58(); virtual void V59();
    virtual void V60(); virtual void V61(); virtual void V62(); virtual void V63();
    virtual void V64(); virtual void V65();
    virtual void UpdateSkeleton(void *Owner, INT A, INT B, INT C, INT *Out, INT D); // slot 66 (+0x108)
    char Pad4[0xb4 - 4];
    FCoords *SpaceBases;                // +0xb4
    INT SpaceBasesNum;                  // +0xb8
    INT GetBoneLines(void *Owner, INT Unused, TArray<FVector> &Out);
};

INT USkeletalMeshInstance_b8100::GetBoneLines(void *Owner, INT Unused, TArray<FVector> &Out)
{
    USkeletalMesh_b8100 *Mesh = GetMesh();
    if (Mesh->HasSkeleton) {
        INT Dummy = 0;
        UpdateSkeleton(Owner, 0, 0, 0, &Dummy, 1);
        INT NumBones = Min(Mesh->RefSkeletonNum, SpaceBasesNum);
        INT First = 0;
        if (NumBones > 1) {
            NumBones--;
            First = 1;
        }
        Out.Empty(sizeof(FVector), NumBones * 2);
        Out.Add(NumBones * 2, sizeof(FVector));
        for (INT i = 0; i < NumBones; i++) {
            Out(i * 2) = SpaceBases[First + i].Origin;
            INT Parent = Mesh->RefSkeleton[First + i].ParentIndex;
            if (Parent != First + i) {
                Out(i * 2 + 1) = SpaceBases[Parent].Origin - SpaceBases[First + i].Origin;
                Out(i * 2 + 1).Normalize();
            } else {
                Out(i * 2 + 1) = GBoxStartMin;
            }
        }
        return NumBones;
    }
    Out.Reset();
    return 0;
}


// ---------------------------------------------------------------------------
// RVA 0xb7fd0: USkeletalMeshInstance vtable slot 71 (0x30a048[71]). Copies the
// location of each bone into a caller buffer with a stride. Neutral names.
struct FBoneSample {                    // 0x20 bytes
    FVector Location;
    FLOAT Pad[5];
};

template<class T> class TBoneArray : public FArray {
public:
    TBoneArray() { Data = 0; ArrayNum = 0; ArrayMax = 0; }
    ~TBoneArray();                       // RVA 0xee510
    INT AddZeroed(INT ElementSize, INT n); // RVA 0x15400
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

// RVA 0x15400: FArray::AddZeroed, copied so the link gives it its retail
// convention (this on the stack).
template<class T> __declspec(noinline) INT TBoneArray<T>::AddZeroed(INT ElementSize, INT n)
{
    INT Index = Add(n, ElementSize);
    char *P = (char *)Data + Index * ElementSize;
    for (INT i = 0; i < n * ElementSize; i++)
        P[i] = 0;
    return Index;
}
template<class T> __declspec(noinline) TBoneArray<T>::~TBoneArray()
{
    ArrayNum = 0;
    if (Data)
        GMalloc->Free(Data);
    Data = 0;
    ArrayMax = 0;
}

struct UnnamedSkelInfo_b7fd0 { char Pad[0x18]; INT NumBones; };
struct USkeletalMesh_b7fd0 {
    char Pad0[0x1ac];
    UnnamedSkelInfo_b7fd0 *SkelInfo;    // +0x1ac
    INT HasSkeleton;                    // +0x1b0
};

class USkeletalMeshInstance_b7fd0;
void UnnamedFillBones_b8860(USkeletalMesh_b7fd0 *Mesh, USkeletalMeshInstance_b7fd0 *Inst, FBoneSample *Samples, INT Stride, INT *Out);

class USkeletalMeshInstance_b7fd0 {
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29(); virtual void V30(); virtual void V31();
    virtual USkeletalMesh_b7fd0 *GetMesh();                       // slot 32 (+0x80)
    virtual void V33(); virtual void V34(); virtual void V35();
    virtual void V36(); virtual void V37(); virtual void V38(); virtual void V39();
    virtual void V40(); virtual void V41(); virtual void V42(); virtual void V43();
    virtual void V44(); virtual void V45(); virtual void V46(); virtual void V47();
    virtual void V48(); virtual void V49(); virtual void V50(); virtual void V51();
    virtual void V52(); virtual void V53(); virtual void V54(); virtual void V55();
    virtual void V56(); virtual void V57(); virtual void V58(); virtual void V59();
    virtual void V60(); virtual void V61(); virtual void V62(); virtual void V63();
    virtual void V64(); virtual void V65();
    virtual void UpdateSkeleton(void *Owner, INT A, INT B, INT C, INT *Out, INT D); // slot 66 (+0x108)
    virtual void V67(); virtual void V68(); virtual void V69(); virtual void V70();
    virtual void GetBoneLocations(void *Owner, FVector *Out, INT Stride, INT *Count); // slot 71
    char Pad4[0xf0 - 4];
    INT Fieldf0;                        // +0xf0
};

void USkeletalMeshInstance_b7fd0::GetBoneLocations(void *Owner, FVector *Out, INT Stride, INT *Count)
{
    USkeletalMesh_b7fd0 *Mesh = GetMesh();
    if (!Mesh->HasSkeleton) {
        *Count = 0;
        return;
    }
    TBoneArray<FBoneSample> Samples;
    Samples.AddZeroed(sizeof(FBoneSample), Mesh->SkelInfo->NumBones);
    INT Dummy = 0;
    UpdateSkeleton(Owner, 0, 0, 0, &Dummy, 1);
    *Count = Min(*Count, Samples.Num());
    Fieldf0 = 0;
    UnnamedFillBones_b8860(Mesh, this, &Samples(0), sizeof(FBoneSample), &Dummy);
    for (INT i = 0; i < *Count; i++) {
        *Out = Samples(i).Location;
        Out = (FVector *)((char *)Out + Stride);
    }
}

// ---------------------------------------------------------------------------
// RVA 0xb82b0: rebuilds the mesh-to-world coordinate system of a skeletal mesh
// instance from its owner (UE2 MeshToWorld style). LTCG: this on the stack,
// ret 8. The FCoords operators use register conventions in retail
// (0x862a0: this ECX, point EDX, result EAX; 0x40f40 and 0x86360: this EAX,
// argument EDI, result EBX); they are defined below so the link reproduces them.
enum ESheerAxis { SHEER_None = 0 };
struct FScale {
    FVector Scale;
    FLOAT SheerRate;
    BYTE SheerAxis;
    FScale() {}
    FScale(const FVector &InScale, FLOAT InSheerRate, ESheerAxis InSheerAxis)
        : Scale(InScale), SheerRate(InSheerRate), SheerAxis((BYTE)InSheerAxis) {}
};

struct FCoordsM {
    FVector Origin, XAxis, YAxis, ZAxis;
    FCoordsM &operator*=(const FVector &Point) { Origin -= Point; return *this; }
    FCoordsM() {}
    FCoordsM(const FVector &InOrigin, const FVector &InX, const FVector &InY, const FVector &InZ)
        : Origin(InOrigin), XAxis(InX), YAxis(InY), ZAxis(InZ) {}
    FCoordsM &operator*=(const FCoordsM &TransformCoords); // RVA 0x40ca0
    FCoordsM &operator*=(const FRotator &Rot);  // RVA 0x40d90
    FCoordsM &operator*=(const FScale &Scale);  // RVA 0x86410
    FCoordsM operator*(const FVector &Point) const;
    FCoordsM operator*(const FRotator &Rot) const;
    FCoordsM operator*(const FScale &Scale) const;
};

struct FGlobalMath {
    FCoordsM UnitCoords;
    void SinCos(INT Angle, FLOAT *OutSin, FLOAT *OutCos);
};
extern FGlobalMath GMath;                 // 0x10ccac00
extern const FVector &GMath_UnitY;        // 0x10ccacb8
extern const FVector &GMath_UnitZ;        // 0x10ccacbc
extern const FVector &GMath_Zero;         // 0x10ccacc0
extern const FVector &GMath_UnitX;        // 0x10ccacc4
FLOAT FSheerSnap(FLOAT Sheer);            // RVA 0x86560

// RVA 0x40d90 (item 0155), copied so the link gives it its retail convention.
__declspec(noinline) FCoordsM &FCoordsM::operator*=(const FRotator &Rot)
{
    FLOAT S, C;
    GMath.SinCos(Rot.Yaw, &S, &C);
    *this *= FCoordsM(GMath_Zero, FVector(+C, +S, 0.f), FVector(-S, +C, 0.f), GMath_UnitZ);
    GMath.SinCos(Rot.Pitch, &S, &C);
    *this *= FCoordsM(GMath_Zero, FVector(+C, 0.f, +S), GMath_UnitY, FVector(-S, 0.f, +C));
    GMath.SinCos(Rot.Roll, &S, &C);
    *this *= FCoordsM(GMath_Zero, GMath_UnitX, FVector(0.f, +C, -S), FVector(0.f, +S, +C));
    return *this;
}

// RVA 0x86410
__declspec(noinline) FCoordsM &FCoordsM::operator*=(const FScale &Scale)
{
    FLOAT Sheer = FSheerSnap(Scale.SheerRate);
    FCoordsM TempCoords = GMath.UnitCoords;
    switch (Scale.SheerAxis) {
        case 1: TempCoords.XAxis.Y = Sheer; break;
        case 2: TempCoords.XAxis.Z = Sheer; break;
        case 3: TempCoords.YAxis.X = Sheer; break;
        case 4: TempCoords.YAxis.Z = Sheer; break;
        case 5: TempCoords.ZAxis.X = Sheer; break;
        case 6: TempCoords.ZAxis.Y = Sheer; break;
        default: break;
    }
    *this *= TempCoords;
    XAxis.X *= Scale.Scale.X; XAxis.Y *= Scale.Scale.Y; XAxis.Z *= Scale.Scale.Z;
    YAxis.X *= Scale.Scale.X; YAxis.Y *= Scale.Scale.Y; YAxis.Z *= Scale.Scale.Z;
    ZAxis.X *= Scale.Scale.X; ZAxis.Y *= Scale.Scale.Y; ZAxis.Z *= Scale.Scale.Z;
    Origin.X /= Scale.Scale.X; Origin.Y /= Scale.Scale.Y; Origin.Z /= Scale.Scale.Z;
    return *this;
}

// RVA 0x862a0
__declspec(noinline) FCoordsM FCoordsM::operator*(const FVector &Point) const
{
    return FCoordsM(*this) *= Point;
}
// RVA 0x40f40
__declspec(noinline) FCoordsM FCoordsM::operator*(const FRotator &Rot) const
{
    return FCoordsM(*this) *= Rot;
}
// RVA 0x86360
__declspec(noinline) FCoordsM FCoordsM::operator*(const FScale &Scale) const
{
    return FCoordsM(*this) *= Scale;
}


class UClass_b82b0 {
public:
    char Pad0[0x28];
    UClass_b82b0 *SuperClass;             // +0x28
};
extern UClass_b82b0 UnnamedClass_10cc1568; // a class object (neutral name)

class AActor_b82b0 {
public:
    char Pad0[0x24];
    UClass_b82b0 *Class;                  // +0x24
    char Pad28[0x80 - 0x28];
    FVector Location;                     // +0x80
    char Pad8c[0xb0 - 0x8c];
    FVector DrawScale3D;                  // +0xb0
    FVector PrePivot;                     // +0xbc
    char Padc8[0xe0 - 0xc8];
    FRotator Rotation;                    // +0xe0
    char Padec[0x23c - 0xec];
    FLOAT DrawScale;                      // +0x23c
    char Pad240[0x37c - 0x240];
    FVector SavedLocation;                // +0x37c (neutral name)
    INT SavedYaw;                         // +0x388 (neutral name)

    UBOOL IsA(UClass_b82b0 *SomeBase) const
    {
        for (UClass_b82b0 *C = Class; C; C = C->SuperClass)
            if (C == SomeBase)
                return 1;
        return 0;
    }
};

struct USkeletalMesh_b82b0 {
    char Pad0[0x74];
    FVector Scale;                        // +0x74
    char Pad80[0x8c - 0x80];
    FRotator RotOrigin;                   // +0x8c
};

class USkeletalMeshInstance_b82b0 {
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29();
    virtual AActor_b82b0 *GetActor();                 // slot 30 (+0x78)
    virtual void V31();
    virtual USkeletalMesh_b82b0 *GetMesh();           // slot 32 (+0x80)
    char Pad4[0x74 - 4];
    INT Field74;                          // +0x74
    char Pad78[0x170 - 0x78];
    INT Field170;                         // +0x170
    char Pad174[0x184 - 0x174];
    UBOOL Field184;                       // +0x184
    FVector Field188;                     // +0x188
    FRotator Field194;                    // +0x194
    FVector Field1a0;                     // +0x1a0
    FRotator Field1ac;                    // +0x1ac
    FCoordsM MeshToWorld;                 // +0x1b8
    INT Field1e8;                         // +0x1e8
    INT Field1ec;                         // +0x1ec
    FCoordsM Coords1f0;                   // +0x1f0
    FCoordsM Coords220;                   // +0x220
    FCoordsM Coords250;                   // +0x250
    FCoordsM Coords280;                   // +0x280

    UBOOL UpdateMeshToWorld(UBOOL bFlag);
};

// RVA 0xb9c40 (this on the stack under LTCG; declared here as a plain function).
void __stdcall UnnamedUpdate_b9c40(USkeletalMeshInstance_b82b0 *Inst, AActor_b82b0 *Owner, UBOOL bFlag);

UBOOL USkeletalMeshInstance_b82b0::UpdateMeshToWorld(UBOOL bFlag)
{
    Field1e8 = 1;
    Field184 = bFlag;
    Field170 = 0;
    USkeletalMesh_b82b0 *Mesh = GetMesh();
    AActor_b82b0 *Owner = GetActor();
    if (!Owner)
        return 0;
    FScale MeshScale(Mesh->Scale * Owner->DrawScale * Owner->DrawScale3D, 0.f, SHEER_None);
    if (Field74)
        MeshToWorld = GMath.UnitCoords * Owner->Location * Owner->Rotation * MeshScale;
    else
        MeshToWorld = GMath.UnitCoords * (Owner->Location + Owner->PrePivot) * Owner->Rotation * Mesh->RotOrigin * MeshScale;
    if (bFlag && Owner->IsA(&UnnamedClass_10cc1568)) {
        Owner->SavedLocation = Owner->Location;
        Owner->SavedYaw = Owner->Rotation.Yaw;
    }
    AActor_b82b0 *Actor = GetActor();
    if (Actor)
        UnnamedUpdate_b9c40(this, Actor, 0);
    Field1a0 = Field188;
    if (bFlag) {
        Coords1f0 = Coords250;
        UnnamedUpdate_b9c40(this, Owner, 1);
    }
    Coords220 = Coords280;
    Field1ac = Field194;
    Field1ec = 0;
    return 1;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Escape(void *);
void Driver_b7f30(UnnamedRotTracker_b7f30 *T, INT *Out)
{
    Escape(T);
    FRotator R = T->ConsumeYawDelta();
    Out[0] = R.Pitch; Out[1] = R.Yaw; Out[2] = R.Roll;
    Escape(T);
}

INT Driver_b8100(USkeletalMeshInstance_b8100 *Inst, void *Owner, TArray<FVector> *Out)
{
    Escape(&GMalloc);
    TArray<FVector> &Lines = *Out;
    INT N = Inst->GetBoneLines(Owner, 0, Lines);
    Escape(&Lines);
    return N;
}

UBOOL Driver_b82b0(USkeletalMeshInstance_b82b0 *Inst, UBOOL bFlag)
{
    Escape(&GMath);
    return Inst->UpdateMeshToWorld(bFlag);
}

void Driver_b7fd0(USkeletalMeshInstance_b7fd0 *Inst, void *Owner, FVector *Out, INT Stride, INT *Count)
{
    Escape(&GMalloc);
    Inst->USkeletalMeshInstance_b7fd0::GetBoneLocations(Owner, Out, Stride, Count);
}
