// Work item 0148: Versus RVA 0x3f390.
// Destructor of UExporter (vtable 0x10c0c9e8, the parent of UObjectExporterT3D).
// UExporter holds SupportedClass at 0x28 and the Formats TArray<FString> at 0x2c;
// the destructor runs ConditionalDestroy(), then the Formats array is destroyed
// and UObject's destructor (RVA 0x15ee0) runs.
#include "versus_build.h"
#include "unreal_object.h"

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
