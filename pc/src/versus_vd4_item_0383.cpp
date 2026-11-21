// Work item 0383: Versus RVA 0xa5a80-0xa5d99. LTCG object (VC7.0 /GL).
// UE2 skeletal-mesh lazy arrays: TArray<FMeshWedge> and TArray<VTriangle>
// serializers, TLazyArray<VTriangle>::Load and the two TLazyArray destructors.
// Element layouts follow UE2 UnSkeletalMesh.h: FMeshWedge is a _WORD vertex
// index plus a two-float UV (sizes 2/4/4); VTriangle is three _WORD wedge
// indices, two BYTE material indices and a DWORD smoothing mask (2/2/2/1/1/4).
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef unsigned short TCHAR;
typedef float FLOAT;

inline void *operator new(unsigned int, void *Mem) { return Mem; }

class UObject;
class FLazyLoader;

struct FCompactIndex
{
    INT Value;
};
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void SerializeBits(void *V, INT LengthBits);    // +0x08
    virtual void SerializeInt(DWORD &Value, DWORD Max);     // +0x0c
    virtual void Preload(UObject *Object);                  // +0x10
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14
    virtual FArchive &operator<<(class FName &N);           // +0x1c
    virtual FArchive &operator<<(UObject *&Res);            // +0x18
    virtual INT MapName(class FName *Name);                 // +0x20
    virtual INT MapObject(UObject *Object);                 // +0x24
    virtual INT Tell();                                     // +0x28
    virtual INT TotalSize();                                // +0x2c
    virtual UBOOL AtEnd();                                  // +0x30
    virtual void Slot34();                                  // +0x34 (unknown)
    virtual void Slot38();                                  // +0x38 (unknown)
    virtual void Seek(INT InPos);                           // +0x3c
    virtual void AttachLazyLoader(FLazyLoader *LazyLoader); // +0x40
    virtual void DetachLazyLoader(FLazyLoader *LazyLoader); // +0x44

    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }
    FArchive &ByteOrderSerialize(void *V, INT Length) { Serialize(V, Length); return *this; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, _WORD &W) { return Ar.ByteOrderSerialize(&W, sizeof(W)); }
    friend FArchive &operator<<(FArchive &Ar, DWORD &D) { return Ar.ByteOrderSerialize(&D, sizeof(D)); }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &F) { return Ar.ByteOrderSerialize(&F, sizeof(F)); }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);   // RVA 0x1ea40

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
    UBOOL ArIsTrans;
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray();
    INT Add(INT Count, INT ElementSize);        // 0x44e0
    void Empty(INT ElementSize, INT Slack);     // 0x4550
};

template <class T> class TArray : public FArray
{
public:
    ~TArray();                                  // retail 0x10aeecc0 (folded across element types)
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    void Empty(INT Slack) { FArray::Empty(sizeof(T), Slack); }

    friend FArchive &operator<<(FArchive &Ar, TArray &A)
    {
        A.CountBytes(Ar);
        if (Ar.IsLoading()) {
            INT NewNum;
            Ar << AR_INDEX(NewNum);
            A.Empty(NewNum);
            for (INT i = 0; i < NewNum; i++)
                Ar << *new(&((T *)A.Data)[A.Add(1, sizeof(T))]) T;
        } else {
            Ar << AR_INDEX(A.ArrayNum);
            for (INT i = 0; i < A.ArrayNum; i++)
                Ar << A(i);
        }
        return Ar;
    }
};

class FLazyLoader
{
public:
    FArchive *SavedAr;
    INT SavedPos;
    FLazyLoader() : SavedAr(0), SavedPos(0) {}
    virtual void Load() = 0;
    virtual void Unload() = 0;
};

template <class T> class TLazyArray : public FLazyLoader, public TArray<T>
{
public:
    ~TLazyArray()
    {
        if (SavedAr)
            SavedAr->DetachLazyLoader(this);
    }
    void Load()
    {
        if (SavedPos > 0) {
            INT PushedPos = SavedAr->Tell();
            SavedAr->Seek(SavedPos);
            *SavedAr << (TArray<T> &)*this;
            SavedPos *= -1;
            SavedAr->Seek(PushedPos);
        }
    }
    void Unload();
};

struct FMeshUV
{
    FLOAT U;
    FLOAT V;
    friend FArchive &operator<<(FArchive &Ar, FMeshUV &M) { return Ar << M.U << M.V; }
};

struct FMeshWedge
{
    _WORD iVertex;
    FMeshUV TexUV;
    friend FArchive &operator<<(FArchive &Ar, FMeshWedge &W) { return Ar << W.iVertex << W.TexUV; }
};

struct VTriangle
{
    _WORD WedgeIndex[3];
    BYTE MatIndex;
    BYTE AuxMatIndex;
    DWORD SmoothingGroups;
    friend FArchive &operator<<(FArchive &Ar, VTriangle &V);
};

// RVA 0xa5ce0. Retail keeps this out of line (six calls in its body); the
// LTCG link here would inline it, so it is marked noinline.
__declspec(noinline) FArchive &operator<<(FArchive &Ar, VTriangle &V)
{
    Ar << V.WedgeIndex[0] << V.WedgeIndex[1] << V.WedgeIndex[2];
    Ar << V.MatIndex << V.AuxMatIndex;
    Ar << V.SmoothingGroups;
    return Ar;
}

// The units, instantiated from the templates above:
// RVA 0xa5a80  operator<<(FArchive&, TArray<FMeshWedge>&)
// RVA 0xa5b80  TLazyArray<FMeshWedge>::~TLazyArray
// RVA 0xa5be0  TLazyArray<VTriangle>::Load
// RVA 0xa5c30  operator<<(FArchive&, TArray<VTriangle>&)
// RVA 0xa5d40  TLazyArray<VTriangle>::~TLazyArray

// Stand-ins for retail callees, defined so the LTCG link gives them their
// retail conventions (archive in ESI and index in EDI for 0x1ea40, as
// published in versus_vd2_item_0116.cpp; `this` on the stack for 0x10aeecc0,
// which has an exception frame in retail).
void External_Scaffold(void *);
struct FScaffoldPart { FScaffoldPart(); ~FScaffoldPart(); };
template <class T> __declspec(noinline) TArray<T>::~TArray() { FScaffoldPart P; External_Scaffold(this); }
FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.IsLoading() && !Ar.IsSaving()) {
        Ar.Serialize(&I.Value, 4);
    } else {
        INT Original = I.Value;
        DWORD V = Original >= 0 ? Original : -Original;
        BYTE B0 = ((I.Value >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40));
        I.Value = 0;
        Ar << B0;
        if (B0 & 0x40) {
            V >>= 6;
            BYTE B1 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
            Ar << B1;
            if (B1 & 0x80) {
                V >>= 7;
                BYTE B2 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                Ar << B2;
                if (B2 & 0x80) {
                    V >>= 7;
                    BYTE B3 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                    Ar << B3;
                    if (B3 & 0x80) {
                        V >>= 7;
                        BYTE B4 = V;
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
    }
    return Ar;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_a5a80(TLazyArray<FMeshWedge> *W, TLazyArray<VTriangle> *T, FArchive *Ar)
{
    Escape(W); Escape(T);
    W->Load();
    T->Load();
    *Ar << (TArray<FMeshWedge> &)*W;
    W->~TLazyArray<FMeshWedge>();
    T->~TLazyArray<VTriangle>();
}
