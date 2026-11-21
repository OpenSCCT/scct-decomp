// Work item 0088 (wave 3): USound default construction (Versus RVA 0xac0b0, 0xac0f0).
// The neighbours are USound's deleting destructor (0xac170) and destructor
// (0xac1a0, members at 0x28, 0x48, 0x6c and 0x78). 0xac0b0 is DECLARE_CLASS's
//     static void InternalConstructor(void* X) { new((EInternal*)X) USound; }
// and 0xac0f0 is USound's default constructor. The member at 0x28 is the
// engine's FSoundData (a TLazyArray<BYTE> plus the owning sound).
typedef unsigned short TCHAR;
typedef unsigned char BYTE;
typedef int INT;
typedef float FLOAT;
typedef unsigned long DWORD;
typedef unsigned int size_t;

enum EInternal { EC_Internal };
inline void* operator new(size_t Size, EInternal* Mem) { return (void*)Mem; }
inline void operator delete(void* Object, EInternal* Mem) {}

class FArchive;

class FArray
{
public:
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : ArrayNum(0), ArrayMax(0), Data(0) {}
    FArray(INT InNum, INT ElementSize) : ArrayNum(InNum), ArrayMax(InNum)
    {
        Data = 0;
        if (ArrayMax)
            Realloc(ElementSize);
    }
    void Realloc(INT ElementSize);
    ~FArray();
};
template<class T> class TArray : public FArray
{
public:
    TArray() {}
    TArray(INT InNum) : FArray(InNum, sizeof(T)) {}
};

class FLazyLoader
{
public:
    FArchive* SavedAr;
    INT SavedPos;
    FLazyLoader() : SavedAr(0), SavedPos(0) {}
    virtual void Load() = 0;
    virtual void Unload() = 0;
};
template<class T> class TLazyArray : public FLazyLoader, public TArray<T>
{
public:
    TLazyArray(INT InNum = 0) : TArray<T>(InNum) {}
    void Load();
    void Unload();
};

class USound;
class FSoundData : public TLazyArray<BYTE>
{
public:
    USound* Owner;
    FSoundData(USound* InOwner) : Owner(InOwner) {}
    void Load();
};

struct FName { INT Index; };

class UObject
{
public:
    virtual ~UObject();
    DWORD UObjectData[9];
    UObject();
};

class USound : public UObject
{
public:
    FSoundData Data;            // 0x28
    FName FileType;             // 0x44
    TArray<BYTE> Field48;       // 0x48
    INT Field54;                // 0x54
    FLOAT Field58;              // 0x58
    INT Field5C;                // 0x5c
    INT Field60;                // 0x60
    FLOAT Field64;              // 0x64
    INT Field68;                // 0x68
    TArray<BYTE> Field6C;       // 0x6c
    TArray<BYTE> Field78;       // 0x78
    __declspec(noinline) USound();
    virtual ~USound();
    static void InternalConstructor(void* X) { new((EInternal*)X) USound; }
};

// UObject.h: the base constructor is defined out of line in Core.
UObject::UObject() {}

// RVA 0xac0f0
USound::USound()
    : Data(this)
{
    Field5C = 0;
    Field58 = -1.f;
    Field64 = 1.f;
}

// Scaffolding for the link, not part of the unit.
void Escape(void*);
void Driver_ac0b0(void* X) { Escape((void*)&USound::InternalConstructor); USound::InternalConstructor(X); }
