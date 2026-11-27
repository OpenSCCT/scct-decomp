// Work item 0385: Versus RVA 0xa5fe0-0xa6394 (Engine, skeletal mesh LOD data;
// LTCG objects).
// 0xa5fe0 TArray<FStaticLODModel>::~TArray, called for USkeletalMesh +0x1ac.
// 0xa6050 TArray<FStaticLODModel>::Remove (Index in EDI, this and Count on
//         the stack, ret 8).
// 0xa60a0 FStaticLODModel::~FStaticLODModel (compiler generated; this on the
//         stack, ret 4). The 0x110-byte record is identified from its lazy
//         arrays and its neighbours (USkeletalMesh); member names are guesses.
// 0xa6180 TLazyArray<FMeshFace>::~TLazyArray (vtable 0x10c09f80).
// 0xa61e0 TLazyArray<FMeshFace>::Load.
// 0xa6230 operator<<(FArchive&, TArray<FMeshFace>&) (Ar in EAX).
// 0xa6330 TArray<UnnamedElement_a63f0>::~TArray (this on the stack).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned short _WORD;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;                 // 0x10c73bf0

class FLazyLoader;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void Slot08(); virtual void Slot0c(); virtual void Slot10();
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14
    virtual void Slot18(); virtual void Slot1c(); virtual void Slot20(); virtual void Slot24();
    virtual INT Tell();                                     // +0x28
    virtual void Slot2c(); virtual void Slot30(); virtual void Slot34(); virtual void Slot38();
    virtual void Seek(INT InPos);                           // +0x3c
    virtual void AttachLazyLoader(FLazyLoader *LazyLoader); // +0x40
    virtual void DetachLazyLoader(FLazyLoader *LazyLoader); // +0x44
    void ByteOrderSerialize(void *V, INT Length) { Serialize(V, Length); }
    UBOOL IsLoading() { return ArIsLoading; }
    INT ArVer, ArNetVer, ArLicenseeVer;
    UBOOL ArIsLoading;                                      // +0x10
    UBOOL ArIsSaving;                                       // +0x14
};

inline FArchive &operator<<(FArchive &Ar, _WORD &W)
{
    Ar.ByteOrderSerialize(&W, sizeof(W));
    return Ar;
}

FArchive &SerializeIndex(FArchive &Ar, INT &Value);   // AR_INDEX, RVA 0x1ea40

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);     // RVA 0x119c0
    INT Add(INT Count, INT ElementSize);                    // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);                 // RVA 0x4550
};

template<class T> class TArray : public FArray
{
public:
    TArray() {}
    __declspec(noinline) ~TArray() { Remove(0, ArrayNum); }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT Add(INT n = 1) { return FArray::Add(n, sizeof(T)); }
    void Empty(INT Slack = 0) { FArray::Empty(sizeof(T), Slack); }
    __declspec(noinline) void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
};

template<class T> inline void *operator new(unsigned int, TArray<T> &Array)
{
    return &Array(Array.Add());
}

template<class T> __declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray<T> &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(T), A.ArrayMax * sizeof(T));
    if (Ar.IsLoading()) {
        INT NewNum;
        SerializeIndex(Ar, NewNum);
        A.Empty(NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << *new(A) T;
    } else {
        SerializeIndex(Ar, A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

class FLazyLoader
{
public:
    FArchive *SavedAr;
    INT SavedPos;
    FLazyLoader() : SavedAr(0), SavedPos(0) {}
    virtual void Load() = 0;
    virtual void Unload() = 0;
};

template<class T> class TLazyArray : public FLazyLoader, public TArray<T>
{
public:
    TLazyArray() {}
    __declspec(noinline) ~TLazyArray()
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

struct FMeshFace
{
    _WORD iWedge[3];
    _WORD MeshMaterialIndex;
    friend FArchive &operator<<(FArchive &Ar, FMeshFace &F)
    {
        return Ar << F.iWedge[0] << F.iWedge[1] << F.iWedge[2] << F.MeshMaterialIndex;
    }
};

// Element types not recovered; sizes chosen only to keep instances distinct.
struct UnnamedElem_a7bf30 { INT A; };
struct UnnamedElem_afb4d0 { INT A[11]; };
struct UnnamedElem_af20d0 { INT A, B, C; };
struct UnnamedElem_aee510 { _WORD A; };
struct UnnamedElem_a5ed0 { INT A, B, C, D, E; };
struct UnnamedElem_a5b80 { INT A, B, C, D, E, F; };
struct UnnamedElem_a5920 { INT A, B, C, D, E, F, G; };

// Stand-in serializers for those element types.
template<class T> inline FArchive &SerializeRaw(FArchive &Ar, T &V) { Ar.Serialize(&V, sizeof(V)); return Ar; }
inline FArchive &operator<<(FArchive &Ar, UnnamedElem_a5ed0 &V) { return SerializeRaw(Ar, V); }
inline FArchive &operator<<(FArchive &Ar, UnnamedElem_a5b80 &V) { return SerializeRaw(Ar, V); }
inline FArchive &operator<<(FArchive &Ar, UnnamedElem_a5920 &V) { return SerializeRaw(Ar, V); }

// Virtual-destructor resource (two at +0x38 and +0x54; destructor RVA 0xc4e0).
class FRawIndexBuffer
{
public:
    virtual ~FRawIndexBuffer();
    INT Pad[6];
};

class FStaticLODModel
{
public:
    TArray<UnnamedElem_a7bf30> Array00;           // +0x00
    TArray<UnnamedElem_afb4d0> Array0c;           // +0x0c
    INT Value18;
    TArray<UnnamedElem_af20d0> Array1c;           // +0x1c
    TArray<UnnamedElem_af20d0> Array28;           // +0x28
    INT Value34;
    FRawIndexBuffer IndexBuffer38;                // +0x38
    FRawIndexBuffer IndexBuffer54;                // +0x54
    INT Pad70[7];
    TArray<UnnamedElem_aee510> Array8c;           // +0x8c
    TLazyArray<UnnamedElem_a5ed0> Lazy98;         // +0x98
    TLazyArray<UnnamedElem_a5b80> LazyB0;         // +0xb0
    TLazyArray<FMeshFace> Faces;                  // +0xc8
    TLazyArray<UnnamedElem_a5920> LazyE0;         // +0xe0
    INT PadF8[6];
};

// 16-byte element with an out-of-line destructor (RVA 0xa63f0).
class UnnamedElement_a63f0
{
public:
    INT A, B, C, D;
    ~UnnamedElement_a63f0();
};

// Scaffolding for the link, not part of the unit.
void Escape(void *);
// Stand-in for the compact index serializer (RVA 0x1ea40), as in the
// published Core unit; only its link-time convention matters here.
__declspec(noinline) FArchive &SerializeIndex(FArchive &Ar, INT &Value)
{
    if (!Ar.ArIsLoading && !Ar.ArIsSaving) {
        Ar.Serialize(&Value, sizeof(INT));
        return Ar;
    }
    DWORD V = Value >= 0 ? Value : -Value;
    unsigned char B0 = (unsigned char)((Value >= 0 ? 0 : 0x80) + (V < 0x40 ? V : (V & 0x3f) + 0x40));
    Value = 0;
    Ar.Serialize(&B0, 1);
    if (B0 & 0x40) {
        V >>= 6;
        unsigned char B1 = (unsigned char)(V < 0x80 ? V : (V & 0x7f) + 0x80);
        Ar.Serialize(&B1, 1);
        if (B1 & 0x80) {
            V >>= 7;
            unsigned char B2 = (unsigned char)(V < 0x80 ? V : (V & 0x7f) + 0x80);
            Ar.Serialize(&B2, 1);
            if (B2 & 0x80) {
                V >>= 7;
                unsigned char B3 = (unsigned char)(V < 0x80 ? V : (V & 0x7f) + 0x80);
                Ar.Serialize(&B3, 1);
                if (B3 & 0x80) {
                    V >>= 7;
                    unsigned char B4 = (unsigned char)V;
                    Ar.Serialize(&B4, 1);
                    Value = B4;
                }
                Value = (Value << 7) + (B3 & 0x7f);
            }
            Value = (Value << 7) + (B2 & 0x7f);
        }
        Value = (Value << 7) + (B1 & 0x7f);
    }
    Value = (Value << 6) + (B0 & 0x3f);
    if (B0 & 0x80)
        Value = -Value;
    return Ar;
}
template<class T> void TLazyArray<T>::Unload() { Escape(this); }
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_a6050(TArray<FStaticLODModel> *A, INT i, INT n, TArray<UnnamedElement_a63f0> *B, void *Mem)
{
    Escape(&GMalloc);
    A->Remove(i, n);
    A->~TArray<FStaticLODModel>();
    B->~TArray<UnnamedElement_a63f0>();
    new (Mem) FStaticLODModel;
}
