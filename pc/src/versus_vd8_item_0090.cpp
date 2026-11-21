// w4_item_0090.cpp -- Versus RVA 0x14c0d0-0x14c246 (Magma smart-pointer list accessor
// and Magma system constructor). Neutral names are used where retail symbols are unknown.

typedef int INT;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef unsigned short TCHAR;
typedef unsigned char BYTE;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};

extern FMalloc *GMalloc;

// Ref-counted object held by the smart pointer returned from 0x14c0d0.
class FMagmaRefCounted_14c0d0 {
public:
    DWORD unk_00;
    INT RefCount;
};

class FMagmaRefPtr_14c0d0 {
public:
    FMagmaRefCounted_14c0d0 *Ptr;

    inline FMagmaRefPtr_14c0d0(const FMagmaRefPtr_14c0d0 &Other) : Ptr(Other.Ptr) {
        if (Ptr) {
            Ptr->RefCount++;
        }
    }

    ~FMagmaRefPtr_14c0d0();
};

class FMagmaRefList_14c0d0 {
public:
    DWORD unk_00;
    FMagmaRefPtr_14c0d0 *Items;

    FMagmaRefPtr_14c0d0 GetItem(INT Index);
};

// FMagmaRefList_14c0d0::GetItem (RVA 0x14c0d0)
// Returns a copy of the ref-counted smart pointer at Items[Index].
FMagmaRefPtr_14c0d0 FMagmaRefList_14c0d0::GetItem(INT Index)
{
    return Items[Index];
}

// Base class providing Magma heap allocation for objects constructed in 0x14c100.
class FMagmaAllocBase_14c100 {
public:
    static inline void *operator new(UINT Size) {
        return GMalloc->Malloc(Size, L"Magma");
    }

    static void operator delete(void *Ptr);
};

class FMagmaHandlerA_14c100 : public FMagmaAllocBase_14c100 {
public:
    virtual ~FMagmaHandlerA_14c100();
};

class FMagmaHandlerB_14c100 : public FMagmaAllocBase_14c100 {
public:
    FMagmaHandlerB_14c100(); // retail 0x2a17c0
    virtual ~FMagmaHandlerB_14c100();
};

class FMagmaHandlerC_14c100 : public FMagmaAllocBase_14c100 {
public:
    virtual ~FMagmaHandlerC_14c100();
};

class FMagmaHandlerD_14c100 : public FMagmaAllocBase_14c100 {
public:
    virtual ~FMagmaHandlerD_14c100();
};

class FMagmaHandlerE_14c100 : public FMagmaAllocBase_14c100 {
public:
    virtual ~FMagmaHandlerE_14c100();
};

class FMagmaHandlerF_14c100 : public FMagmaAllocBase_14c100 {
public:
    virtual ~FMagmaHandlerF_14c100();
};

void RegisterMagmaHandlers_10ba04e0(
    FMagmaHandlerC_14c100 *C,
    FMagmaHandlerB_14c100 *B,
    FMagmaHandlerA_14c100 *A);
void InitMagmaSubSystem_10a4c460();
void RegisterMagmaHandlerD_10ba1880(FMagmaHandlerD_14c100 *D);
void RegisterMagmaHandlerE_10ba21b0(FMagmaHandlerE_14c100 *E);
void RegisterMagmaHandlerF_10b9ef70(FMagmaHandlerF_14c100 *F);

class FMagmaSystemBase_14c100 {
public:
    FMagmaSystemBase_14c100(); // retail 0x29f4d0
    virtual ~FMagmaSystemBase_14c100();

    BYTE unk_04[0x30];
};

class FMagmaSystem_14c100 : public FMagmaSystemBase_14c100 {
public:
    void *unk_34;
    void *unk_38;

    FMagmaSystem_14c100();
    virtual ~FMagmaSystem_14c100();
};

// FMagmaSystem_14c100::FMagmaSystem_14c100 (RVA 0x14c100)
// Constructs the Magma system object and allocates/registers its helper objects.
FMagmaSystem_14c100::FMagmaSystem_14c100()
    : unk_34(0)
    , unk_38(0)
{
    RegisterMagmaHandlers_10ba04e0(
        new FMagmaHandlerC_14c100(),
        new FMagmaHandlerB_14c100(),
        new FMagmaHandlerA_14c100());
    InitMagmaSubSystem_10a4c460();
    RegisterMagmaHandlerD_10ba1880(new FMagmaHandlerD_14c100());
    RegisterMagmaHandlerE_10ba21b0(new FMagmaHandlerE_14c100());
    RegisterMagmaHandlerF_10b9ef70(new FMagmaHandlerF_14c100());
}

// Scaffolding for the LTCG link, not part of the unit.
inline void *operator new(UINT, void *Mem) { return Mem; }
void Escape(void *);

void Driver_14c0d0(FMagmaRefList_14c0d0 *List, INT Index)
{
    FMagmaRefPtr_14c0d0 Item = List->GetItem(Index);
    Escape(&Item);
}

void Driver_14c100(FMagmaSystem_14c100 *Obj)
{
    Escape(&GMalloc);
    new (Obj) FMagmaSystem_14c100();
}
