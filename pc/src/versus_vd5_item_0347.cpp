// Work item 0347: RVA 0x110d40-0x111046.
typedef unsigned long DWORD;
typedef int INT;
typedef unsigned short TCHAR;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

// 0x110de0: frees a heap block held at offset 8 (FArray-like Data pointer).
// Owner unidentified; neutral name.
struct UnnamedClass_110de0 {
    INT Pad0;
    INT Pad4;
    void *Data;
    void Free();
};
void UnnamedClass_110de0::Free()
{
    if (Data)
        GMalloc->Free(Data);
    Data = 0;
}

// 0x110d40: destructor of a UObject subclass (the deleting destructor at
// 0x110d10 is UFont's, so this is likely UFont::~UFont).
class UObject {
public:
    INT Index;       // 0x04
    virtual ~UObject();
};

#define INDEX_NONE -1
#define RF_Destroyed 0x00800000
#define RF_Unreachable 0x80000000

// Member destructors (RVA 0x1f20d0, 0x17bf30, 0x110ca0): LTCG gave them
// `this` on the stack. Bodies stand in so the linker sees local functions.
class FArray {
public:
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};
struct FMember28 : public FArray { __declspec(noinline) ~FMember28() { Release(this, ArrayNum); } static void Release(FMember28 *, INT); };
struct FMember34 : public FArray { __declspec(noinline) ~FMember34() { Release(this, ArrayNum); } static void Release(FMember34 *, INT); };
struct FMember40 : public FArray { __declspec(noinline) ~FMember40() { Release(this, ArrayNum); } static void Release(FMember40 *, INT); };

class UFont : public UObject {
public:
    INT Pad08, Pad0C, Pad10, Pad14, Pad18;
    DWORD ObjectFlags;  // 0x1c (really UObject's)
    INT Pad20, Pad24;
    FMember28 M28;
    FMember34 M34;
    FMember40 M40;
    virtual ~UFont();
    virtual void V1();
    virtual void V2();
    virtual void V3();
    virtual void V4();
    virtual void V5();
    virtual void V6();
    virtual void V7();
    virtual void V8();
    __declspec(dllimport) void Destroy();
};

UFont::~UFont()
{
    if (Index != INDEX_NONE && !(ObjectFlags & RF_Destroyed)) {
        ObjectFlags = (ObjectFlags & ~(RF_Destroyed | RF_Unreachable)) | RF_Destroyed;
        Destroy();
    }
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_110d40(UFont *A, UFont *B)
{
    A->UFont::~UFont();
    B->UFont::~UFont();
    Escape(A);
}
