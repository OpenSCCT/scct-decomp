// Work item 0111 (wave 3): Versus RVA 0xb47c0 and 0xb4830, both from an LTCG
// (VC7.0 /GL) object of the skeletal animation code.
//  0xb47c0  MotionChunk::~MotionChunk   (implicit destructor; this on the stack, LTCG.
//           Left compiler-generated: a user-declared one keeps a derived vptr store)
//  0xb4830  UMeshAnimation::Serialize   (vtable UMeshAnimation slot 10)
// MotionChunk layout follows Unreal Engine 2 (UnSkeletalMesh.h) with a
// polymorphic base at offset 0 (vtable 0x10c049cc: virtual destructor plus
// pure virtuals; its deleting destructor is 0x109c3ad0).  The base is named
// neutrally (UnnamedMotionBase_3049cc) since no label names it.
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned short TCHAR;
typedef float FLOAT;
typedef unsigned char BYTE;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

inline void operator delete(void *Ptr) { GMalloc->Free(Ptr); }
inline void *operator new(unsigned int, void *Mem) { return Mem; }

class FName { public: INT Index; };

class FArchive {
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    virtual void SerializeBits(void *V, INT LengthBits);
    virtual void SerializeInt(DWORD &Value, DWORD Max);
    virtual void Preload(class UObject *Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    virtual FArchive &operator<<(class FName &N);
    virtual FArchive &operator<<(class UObject *&Res);
    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    INT ArIsLoading;
    INT ArIsSaving;
    friend FArchive &operator<<(FArchive &Ar, BYTE &V) { Ar.Serialize(&V, 1); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, INT &V) { Ar.Serialize(&V, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, DWORD &V) { Ar.Serialize(&V, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &V) { Ar.Serialize(&V, 4); return Ar; }
};

class FCompactIndex {
public:
    INT Value;
    friend __declspec(noinline) FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
    {
        if (!Ar.ArIsLoading && !Ar.ArIsSaving) {
            Ar << I.Value;
        } else {
            INT Original = I.Value;
            DWORD V = Original >= 0 ? Original : -Original;
            BYTE B0 = (BYTE)((Original >= 0 ? 0 : 0x80) + (V < 0x40 ? V : (V & 0x3f) + 0x40));
            I.Value = 0;
            Ar << B0;
            if (B0 & 0x40) {
                V >>= 6;
                BYTE B1 = (BYTE)(V < 0x80 ? V : (V & 0x7f) + 0x80);
                Ar << B1;
                if (B1 & 0x80) {
                    V >>= 7;
                    BYTE B2 = (BYTE)(V < 0x80 ? V : (V & 0x7f) + 0x80);
                    Ar << B2;
                    if (B2 & 0x80) {
                        V >>= 7;
                        BYTE B3 = (BYTE)(V < 0x80 ? V : (V & 0x7f) + 0x80);
                        Ar << B3;
                        if (B3 & 0x80) {
                            V >>= 7;
                            BYTE B4 = (BYTE)V;
                            Ar << B4;
                            I.Value = B4;
                        }
                        I.Value = (I.Value << 7) + (B3 & 0x7f);
                    }
                    I.Value = (I.Value << 7) + (B2 & 0x7f);
                }
                I.Value = (I.Value << 7) + (B1 & 0x7f);
            }
            I.Value = (I.Value << 6) + (B0 & 0x3f);
            if (B0 & 0x80)
                I.Value = -I.Value;
            if (Ar.ArIsSaving && I.Value != Original)
                I.Value = Original;
        }
        return Ar;
    }
};
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    ~FArray()
    {
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    INT Add(INT Count, INT ElementSize);
    void Remove(INT Index, INT Count, INT ElementSize);
    void Empty(INT ElementSize, INT Slack);
};

template <class T> class TArray;
template <class T> inline void *operator new(unsigned int, TArray<T> &A);

template <class T> class TArray : public FArray {
public:
    ~TArray();
    void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    __declspec(noinline) void Empty(INT Slack = 0)
    {
        for (INT i = 0; i < ArrayNum; i++)
            (&(*this)(i))->~T();
        FArray::Empty(sizeof(T), Slack);
    }
    friend __declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray &A)
    {
        A.CountBytes(Ar);
        if (Ar.ArIsLoading) {
            INT NewNum;
            Ar << AR_INDEX(NewNum);
            A.Empty(NewNum);
            for (INT i = 0; i < NewNum; i++)
                Ar << *new (A) T;
        } else {
            Ar << AR_INDEX(A.ArrayNum);
            for (INT i = 0; i < A.ArrayNum; i++)
                Ar << A(i);
        }
        return Ar;
    }
};
template <class T> inline void *operator new(unsigned int, TArray<T> &A)
{
    INT Index = A.Add(1, sizeof(T));
    return &A(Index);
}

class UObject;
struct FQuat {
    FLOAT X, Y, Z, W;
    friend FArchive &operator<<(FArchive &Ar, FQuat &Q) { return Ar << Q.X << Q.Y << Q.Z << Q.W; }
};
struct FVector {
    FLOAT X, Y, Z;
    friend FArchive &operator<<(FArchive &Ar, FVector &V) { return Ar << V.X << V.Y << V.Z; }
};

// TArray<T>::~TArray is { Remove(0, ArrayNum); } (out of line, e.g. the shared
// pointer-array copy at 0x1091ef20); the AnalogTrack copy lives in this unit.

struct AnalogTrack {
    DWORD Flags;
    TArray<FQuat> KeyQuat;
    TArray<FVector> KeyPos;
    TArray<FLOAT> KeyTime;
    __declspec(noinline) ~AnalogTrack() {}
    friend __declspec(noinline) FArchive &operator<<(FArchive &Ar, AnalogTrack &T)
    {
        return Ar << T.Flags << T.KeyQuat << T.KeyPos << T.KeyTime;
    }
};

class UnnamedMotionBase_3049cc {
public:
    virtual ~UnnamedMotionBase_3049cc() {}
    virtual void Slot1() = 0;
    virtual void Slot2() = 0;
};

struct MotionChunk : public UnnamedMotionBase_3049cc {
    FVector RootSpeed3D;
    FLOAT TrackTime;
    INT StartBone;
    DWORD Flags;
    TArray<INT> BoneIndices;
    TArray<AnalogTrack> AnimTracks;
    AnalogTrack RootTrack;
    TArray<AnalogTrack> ExtraTracks;   // name unknown
    __declspec(noinline) MotionChunk() {}
    void Slot1();
    void Slot2();
    friend __declspec(noinline) FArchive &operator<<(FArchive &Ar, MotionChunk &M)
    {
        return Ar << M.RootSpeed3D << M.TrackTime << M.StartBone << M.Flags
                  << M.BoneIndices << M.AnimTracks << M.RootTrack;
    }
};


template <> __declspec(noinline) TArray<AnalogTrack>::~TArray() { Remove(0, ArrayNum); }


// UObject from Unreal Engine 2 (0x28 bytes); Serialize is retail 0x10915f50.
class UObject {
public:
    UObject();
    virtual ~UObject();
    virtual void Serialize(FArchive &Ar);
    DWORD ObjectData[9];
};

struct FNamedBone {
    FName Name;
    DWORD Flags;
    INT ParentIndex;
    friend FArchive &operator<<(FArchive &Ar, FNamedBone &B)
    {
        return Ar << B.Name << B.Flags << B.ParentIndex;
    }
};

class UAnimNotify;
struct FMeshAnimNotify {
    FLOAT Time;
    FName Function;
    UAnimNotify *NotifyObject;
    friend FArchive &operator<<(FArchive &Ar, FMeshAnimNotify &N)
    {
        return Ar << N.Time << N.Function << *(UObject **)&N.NotifyObject;
    }
};

struct FMeshAnimSeq {
    FName Name;
    TArray<FName> Groups;
    INT StartFrame;
    INT NumFrames;
    FLOAT Rate;
    TArray<FMeshAnimNotify> Notifys;
    INT Unknown28;              // SCCT addition, serialised from version 0x73
    __declspec(noinline) FMeshAnimSeq() {}
    friend __declspec(noinline) FArchive &operator<<(FArchive &Ar, FMeshAnimSeq &S)
    {
        if (Ar.ArVer >= 0x73)
            Ar << S.Unknown28;
        else
            S.Unknown28 = 0;
        Ar << S.Name << S.Groups << S.StartFrame << S.NumFrames << S.Notifys << S.Rate;
        return Ar;
    }
};

class UMeshAnimation : public UObject {
public:
    INT InternalVersion;
    TArray<FNamedBone> RefBones;
    TArray<MotionChunk> Moves;
    TArray<FMeshAnimSeq> AnimSeqs;
    void Serialize(FArchive &Ar);
};

void UMeshAnimation::Serialize(FArchive &Ar)
{
    UObject::Serialize(Ar);
    Ar << InternalVersion;
    Ar << RefBones;
    Ar << Moves;
    Ar << AnimSeqs;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_b47c0(MotionChunk *M)
{
    Escape(&GMalloc);
    M->MotionChunk::~MotionChunk();
}
void Driver_b4830(void *A)
{
    // Construct one so the vtable (and its Serialize slot) is emitted.
    Escape(new (A) UMeshAnimation);
}
