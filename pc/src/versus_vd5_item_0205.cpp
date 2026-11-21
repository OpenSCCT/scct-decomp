// Work item 0205: Versus RVA 0xe6240 and 0xe62f0.
// Class names are neutral (UnnamedClass<vtable RVA>) because no registered
// name identifies these vtables.
enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned __int64 QWORD;

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

class FString {
public:
    ~FString();
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray {
public:
    ~TArray();
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
};

// Parent class; its destructor is matched in versus_more_object_destructors.cpp.
class UnnamedClass30D7D8 : public UObject {
public:
    virtual ~UnnamedClass30D7D8();
    unsigned UnnamedClass30D7D8Data[2];
};

// Secondary interface base (vtable at +0x28), trivially destructible like FExec.
class FUnnamedInterface3043AC {
public:
    virtual void VirtualSlot0();
};

class UnnamedClass304338 : public UnnamedClass30D7D8, public FUnnamedInterface3043AC {
public:
    virtual ~UnnamedClass304338();
    unsigned char Data2C[0x54 - 0x2c];
    FString Field54;
    FString Field60;
    unsigned char Data6C[0x74 - 0x6c];
    TArray<FString> Field74;
    FString Field80;
};

// RVA 0xe6240
UnnamedClass304338::~UnnamedClass304338() { ConditionalDestroy(); }

// RVA 0xe62f0: constructor; this arrives in ESI and the argument in EAX (LTCG).
// The serial counter was a global shared by every instance.
extern QWORD GUnnamedSerial_e62f0;

inline void *operator new(unsigned int, void *Mem) { return Mem; }

#pragma pack(push, 4)
class FUnnamedRecord3042CC {
public:
    FUnnamedRecord3042CC(INT InValue);
    virtual void VirtualSlot0();
    INT Value;
    QWORD Id;
};
#pragma pack(pop)

#pragma auto_inline(off)
FUnnamedRecord3042CC::FUnnamedRecord3042CC(INT InValue)
    : Value(InValue)
{
    QWORD NewId = GUnnamedSerial_e62f0++ * 0x100 + 0xe0;
    Id = NewId;
}
#pragma auto_inline(on)

// Scaffolding for the link, not part of the unit.
void Use(FUnnamedRecord3042CC *);
void Driver_e62f0(void *A, void *B, INT X, INT Y)
{
    Use(new (A) FUnnamedRecord3042CC(X));
    Use(new (B) FUnnamedRecord3042CC(Y));
}
