// Work item 0378: Versus RVA 0xa4dc0, the USkeletalMeshInstance default
// constructor compiled with /GL and linked with /LTCG (`this` arrives in EDI).
// The class identity comes from the matching destructor at 0xa4f40, which
// installs the same vtable (0x10c0a048) and chains to ~ULodMeshInstance.
// Field names are neutral; only the layout is recovered.
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef unsigned __int64 QWORD;

#pragma pack(push, 4)

inline void *operator new(unsigned, void *Where) { return Where; }

class FVector
{
public:
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
};

template <class T> class TArray
{
public:
    TArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~TArray();
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
};

// Engine globals holding pointers to the default vectors copied by
// ULodMeshInstance (names unknown).
extern FVector *GUnnamedVector_10ccacc4;
extern FVector *GUnnamedVector_10ccacc0;

// Running counter behind MakeCacheID (a local static in the original).
extern QWORD MakeCacheID_Counter;

// 16-byte array-like member of ULodMeshInstance at +0x40 (type unknown):
// three TArray-style fields plus one more, all cleared by its constructor.
struct FUnnamedArray16
{
    FUnnamedArray16() : Data(0), Num(0), Max(0), Extra(0) {}
    void *Data;
    INT Num;
    INT Max;
    INT Extra;
};

class UObject
{
public:
    UObject() {}
    virtual ~UObject();
    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    INT Name;
    void *Class;
};

class UMeshInstance : public UObject
{
public:
    UMeshInstance() {}
    virtual ~UMeshInstance();
};

class ULodMeshInstance : public UMeshInstance
{
public:
    ULodMeshInstance()
        : Vector28(*GUnnamedVector_10ccacc4), Vector34(*GUnnamedVector_10ccacc0)
    {
    }
    virtual ~ULodMeshInstance();
    FVector Vector28;
    FVector Vector34;
    FUnnamedArray16 Array40;
    INT Unknown50[11];
};

// Render resource embedded at +0x7c (vtable 0x10c0a020): an index buffer
// with a cache id made from base 0xe1.
class FRenderResource
{
public:
    virtual ~FRenderResource();
    INT Value4;
    INT Value8;
    QWORD CacheId;
    INT Revision;
    INT Value18;
    INT Value1c;
};

class FUnnamedIndexBuffer_a5140 : public FRenderResource
{
public:
    FUnnamedIndexBuffer_a5140();
    virtual ~FUnnamedIndexBuffer_a5140();
    TArray<unsigned short> Indices;
};

FUnnamedIndexBuffer_a5140::FUnnamedIndexBuffer_a5140()
{
    Value4 = 0;
    Value8 = 0;
    CacheId = MakeCacheID_Counter++ * 256 + 0xe1;
    Revision = 1;
    Value18 = 0;
    Value1c = 0;
}

class USkeletalMeshInstance : public ULodMeshInstance
{
public:
    USkeletalMeshInstance();
    virtual ~USkeletalMeshInstance();
    FUnnamedIndexBuffer_a5140 IndexBuffer;   // +0x7c
    TArray<INT> ArrayA8;
    TArray<INT> ArrayB4;
    INT UnknownC0[16];
    TArray<INT> Array100;
    TArray<INT> Array10C;
    TArray<INT> Array118;
    TArray<INT> Array124;
    INT Unknown130[2];
    TArray<INT> Array138;
    TArray<INT> Array144;
    TArray<INT> Array150;
    INT Unknown15C[2];
    INT Value164;
    INT Unknown168[4];
    TArray<INT> Array178;
    INT Unknown184[97];
    INT Value308;
    INT Value30C;
    INT Unknown310[16];
    FLOAT Value350;
    FLOAT Value354;
    INT Value358;
    INT Value35C;
    TArray<INT> Array360;
};

USkeletalMeshInstance::USkeletalMeshInstance()
{
    Value164 = 0;
    Value308 = 0;
    Value358 = 0;
    Value35C = 0;
    Value30C = 0;
    Value350 = 8.0f;
    Value354 = 8.0f;
}

#pragma pack(pop)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_a4dc0(void *Mem)
{
    Escape(&GUnnamedVector_10ccacc4);
    Escape(&GUnnamedVector_10ccacc0);
    Escape(&MakeCacheID_Counter);
    new (Mem) USkeletalMeshInstance;
}
