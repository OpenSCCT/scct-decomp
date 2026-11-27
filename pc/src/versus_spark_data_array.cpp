#include "versus_build.h"
#include "unreal_object.h"
#include "unreal_math.h"

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArray {
public:
    void *Data;
    INT ArrayNum, ArrayMax;

    ~FArray() {
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);
};

template<class T> class TArray : public FArray {
public:
    ~TArray() {
        for (INT i = 0; i < ArrayNum; ++i)
            ((T *)Data)[i].~T();
        FArray::Remove(0, ArrayNum, sizeof(T));
    }
};

// The Versus Engine package serializes this struct as two floats followed by two vectors.
struct FParticleSparkData {
    FLOAT TimeBeforeVisible, TimeBetweenSegments;
    FVector StartLocation, StartVelocity;
};

class UParticleEmitter : public UObject {
public:
    virtual ~UParticleEmitter();
    virtual void Destroy();
    virtual void VirtualSlot22();
    virtual void CleanUp();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    BYTE Unknown028[0x3e8 - 0x28];
};
class USparkEmitter : public UParticleEmitter {
public:
    virtual ~USparkEmitter();
    BYTE Unknown3e8[0x18];
    TArray<FParticleSparkData> SparkData;
    BYTE Unknown40c[0x18];
};

void UParticleEmitter::Destroy()
{
    CleanUp();
    UObject::Destroy();
}

USparkEmitter::~USparkEmitter()
{
    ConditionalDestroy();
}

typedef char SparkData_size[sizeof(FParticleSparkData) == 0x20 ? 1 : -1];
typedef char SparkEmitter_size[sizeof(USparkEmitter) == 0x424 ? 1 : -1];
