// Work item 0148: Versus RVA 0x3f390.
// Destructor of UExporter (vtable 0x10c0c9e8, the parent of UObjectExporterT3D).
// UExporter holds SupportedClass at 0x28 and the Formats TArray<FString> at 0x2c;
// the destructor runs ConditionalDestroy(), then the Formats array is destroyed
// and UObject's destructor (RVA 0x15ee0) runs.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;

enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template <class T> class TArray : public FArray {
public:
    ~TArray();
};

class FString : public TArray<TCHAR> {
public:
    ~FString();
};

class UClass;

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
    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    INT Name;
    UClass *Class;
    INT ConditionalDestroy()
    {
        if (Index != INDEX_NONE && !(ObjectFlags & RF_Destroyed)) {
            ObjectFlags = (ObjectFlags & ~(RF_DebugDestroy | RF_Destroyed)) | RF_Destroyed;
            Destroy();
            return 1;
        }
        return 0;
    }
};

class UExporter : public UObject {
public:
    UClass *SupportedClass;     // 0x28
    TArray<FString> Formats;    // 0x2c
    virtual ~UExporter();
};

UExporter::~UExporter()
{
    ConditionalDestroy();
}
