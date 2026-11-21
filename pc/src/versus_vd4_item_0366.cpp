// Work item 0366: Versus RVA 0xa2eb0-0xa2f94.
// 0xa2eb0: UERainPrimitive destructor (its deleting destructor is at 0xa2e80).
// 0xa2f40: constructor of a render resource (LTCG, this in ESI); class name not
// recovered, so it is called FRenderResource_A2F40.
typedef unsigned long DWORD;
typedef int INT;
typedef unsigned __int64 QWORD;

enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

class UObject {
public:
    virtual ~UObject();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
    int Index;
    unsigned Reserved[5];
    unsigned ObjectFlags;
    int ConditionalDestroy()
    {
        if (Index != INDEX_NONE && !(ObjectFlags & RF_Destroyed)) {
            ObjectFlags = (ObjectFlags & ~(RF_DebugDestroy | RF_Destroyed)) | RF_Destroyed;
            Destroy();
            return 1;
        }
        return 0;
    }
};

class UPrimitive : public UObject {
public:
    virtual ~UPrimitive();
    DWORD PrimitiveData[14];   // 0x20..0x57, not touched here
};

// Member at 0x58: its out-of-line cleanup (0xaedf20) takes the member by pointer.
struct FRainMember58;
void __stdcall DestroyRainMember58(FRainMember58 *Member);
struct FRainMember58 {
    DWORD Data[7];
    ~FRainMember58() { DestroyRainMember58(this); }
};

// Member at 0x74 with an out-of-line destructor (0x90c4e0).
struct FRainMember74 {
    DWORD Data[3];
    ~FRainMember74();
};

class UERainPrimitive : public UPrimitive {
public:
    virtual ~UERainPrimitive();
    FRainMember58 Member58;
    FRainMember74 Member74;
};

UERainPrimitive::~UERainPrimitive() { ConditionalDestroy(); }

// ---------------------------------------------------------------------------
// 0xa2f40: render-resource constructor. The cache id is the global counter
// shifted into the high bits plus the resource type 0xE1 (UE2 MakeCacheID).
extern QWORD GCacheIdCounter;   // 0x10c96930
inline QWORD MakeCacheID(INT Base)
{
    return GCacheIdCounter++ * 256 + Base;
}

#pragma pack(push, 4)
class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
};
class FRenderResource_A2F40 {
public:
    virtual INT GetCacheIdSlot();
    FArray Items;
    QWORD CacheId;
    INT Revision;
    FRenderResource_A2F40();
};
#pragma pack(pop)

__declspec(noinline) FRenderResource_A2F40::FRenderResource_A2F40()
{
    CacheId = MakeCacheID(0xE1);
    Revision = 0;
}

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);
void Driver_a2f40(void *Mem)
{
    Escape(new(Mem) FRenderResource_A2F40);
}
