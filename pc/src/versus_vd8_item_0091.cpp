// w4_item_0091.cpp -- Versus RVA 0x14c280-0x14c4c8 (Magma subsystem destructors, init, archive serialization)

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

// Engine allocator (from unreal_containers.h).
class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
};

extern FMalloc *GMalloc;
extern const TCHAR GMagmaAllocTag[];

inline void *operator new(unsigned int Size)
{
    return GMalloc->Malloc(Size, GMagmaAllocTag);
}

inline void operator delete(void *Ptr)
{
    GMalloc->Free(Ptr);
}

// ---------------------------------------------------------------------------
// RVA 0x14c280 -- scalar deleting destructor for Magma helper class (vtable 0x303480)
// ---------------------------------------------------------------------------

class FMagmaFactoryBase {
public:
    virtual ~FMagmaFactoryBase() {}
    virtual void VirtualSlot1() = 0;
};

class FMagmaFactory : public FMagmaFactoryBase {
public:
    virtual void VirtualSlot1();
};

// ---------------------------------------------------------------------------
// RVA 0x14c2c0 & 0x14c460 -- Magma pool init and Magma manager destructor
// ---------------------------------------------------------------------------

class FMagmaPool {
public:
    FMagmaPool();
    ~FMagmaPool();

    BYTE unk_00[0x20];
};

extern FMagmaPool *GMagmaPool;

void MagmaShutdownA();
void MagmaShutdownB();
void MagmaShutdownC();
void MagmaShutdownD();

class FMagmaManagerBase {
public:
    virtual ~FMagmaManagerBase();
};

class FMagmaManager : public FMagmaManagerBase {
public:
    virtual ~FMagmaManager();
};

FMagmaManager::~FMagmaManager()
{
    delete GMagmaPool;
    GMagmaPool = 0;
    MagmaShutdownA();
    MagmaShutdownB();
    MagmaShutdownC();
    MagmaShutdownD();
}

void InitMagmaPool()
{
    GMagmaPool = new FMagmaPool();
}

// ---------------------------------------------------------------------------
// RVA 0x14c350 -- Magma archive serialization
// ---------------------------------------------------------------------------

class UObject;

class FArchive {
public:
    virtual ~FArchive();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual FArchive &operator<<(UObject *&Res);

    INT   ArVer;
    INT   ArNetVer;
    INT   ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;

    UBOOL IsLoading() const { return ArIsLoading; }
    UBOOL IsSaving() const { return ArIsSaving; }
};

// Minimal VC7.0 std::vector<T*> layout (_Ptrit-style iterator)
template<class T>
struct FPtrIt {
    T *Current;
    FPtrIt() : Current(0) {}
    FPtrIt(T *P) : Current(P) {}
    T *Base() const { return Current; }
    T &operator*() const { return *Current; }
    FPtrIt &operator++() { ++Current; return *this; }
    FPtrIt operator++(int) { FPtrIt Tmp = *this; ++Current; return Tmp; }
};

template<class T>
inline bool operator==(const FPtrIt<T> &Left, const FPtrIt<T> &Right)
{
    return Left.Base() == Right.Base();
}

template<class T>
inline bool operator!=(const FPtrIt<T> &Left, const FPtrIt<T> &Right)
{
    return !(Left == Right);
}

template<class T>
struct FStdVector {
    typedef FPtrIt<T> Iterator;

    INT AllocPad;
    T  *First;
    T  *Last;
    T  *End;

    Iterator Begin() { return Iterator(First); }
    Iterator EndPtr() { return Iterator(Last); }
    INT Size() const { return First == 0 ? 0 : (INT)(Last - First); }
};

struct FMagmaSceneEntry {
    BYTE     unk_00[0x2c];
    UObject *Object;

    void Serialize(FArchive &Ar)
    {
        if (!Ar.IsLoading() && !Ar.IsSaving()) {
            if (Object != 0) {
                Ar << Object;
            }
        }
    }
};

struct FMagmaGroup {
    BYTE                           unk_00[0x14];
    FStdVector<FMagmaSceneEntry *> Entries;
};

struct FMagmaGroupNode {
    FMagmaGroupNode *Next;
    FMagmaGroupNode *Prev;
    FMagmaGroup     *Value;
};

struct FMagmaGroupList {
    struct Iterator {
        FMagmaGroupNode *Ptr;
        Iterator() : Ptr(0) {}
        Iterator(FMagmaGroupNode *P) : Ptr(P) {}
        FMagmaGroup *&operator*() const { return Ptr->Value; }
        Iterator &operator++() { Ptr = Ptr->Next; return *this; }
        bool operator==(const Iterator &Other) const { return Ptr == Other.Ptr; }
        bool operator!=(const Iterator &Other) const { return !(*this == Other); }
    };

    INT              AllocPad;
    FMagmaGroupNode *Head;
    UINT             Size;

    Iterator Begin() const { return Iterator(Head == 0 ? 0 : Head->Next); }
    Iterator End() const { return Iterator(Head); }
};

struct FMagmaContext {
    void           *Vtable;
    FMagmaGroupList Groups;

    void Serialize(FArchive &Ar);
};

class FMagmaRefObject {
public:
    virtual ~FMagmaRefObject();
    DWORD RefCount;
    BYTE  unk_08[0x468];
    BYTE  NumRefs;
    BYTE  unk_471[0x7];
    UObject **Refs;

    void SerializeRefs(FArchive &Ar);
};

void FMagmaRefObject::SerializeRefs(FArchive &Ar)
{
    for (INT i = 0; i < (INT)NumRefs; i++) {
        if (!Ar.IsLoading() && !Ar.IsSaving()) {
            if (Refs[i] != 0) {
                Ar << Refs[i];
            }
        }
    }
}

template<class T>
class FMagmaSmartPtr {
public:
    T *Ptr;

    FMagmaSmartPtr(T *InPtr) : Ptr(InPtr)
    {
        if (Ptr != 0) {
            Ptr->RefCount++;
        }
    }

    ~FMagmaSmartPtr()
    {
        if (Ptr != 0) {
            if (Ptr->RefCount <= 1) {
                delete Ptr;
            } else {
                Ptr->RefCount--;
            }
        }
    }

    T *operator->() const { return Ptr; }
};

class FMagmaResourceManager {
public:
    FStdVector<FMagmaRefObject *> Resources;

    INT GetCount() const { return Resources.Size(); }
    FMagmaSmartPtr<FMagmaRefObject> GetResource(INT Index);
};

FMagmaSmartPtr<FMagmaRefObject> FMagmaResourceManager::GetResource(INT Index)
{
    return FMagmaSmartPtr<FMagmaRefObject>(Resources.First[Index]);
}

FMagmaResourceManager *GetMagmaResourceManager();

void FMagmaContext::Serialize(FArchive &Ar)
{
    if (Ar.IsLoading() || Ar.IsSaving()) {
        return;
    }

    for (FMagmaGroupList::Iterator It = Groups.Begin(); It != Groups.End(); ++It) {
        for (FStdVector<FMagmaSceneEntry *>::Iterator EntryIt = (*It)->Entries.Begin(); ; ++EntryIt) {
            FStdVector<FMagmaSceneEntry *>::Iterator EndIt = (*It)->Entries.EndPtr();
            if (EntryIt == EndIt) {
                break;
            }
            (*EntryIt)->Serialize(Ar);
        }
    }

    for (INT i = 0; i < GetMagmaResourceManager()->GetCount(); i++) {
        GetMagmaResourceManager()->GetResource(i)->SerializeRefs(Ar);
    }
}

// ---------------------------------------------------------------------------
// Scaffolding for LTCG links, not part of the units.
// ---------------------------------------------------------------------------
void Escape(void *);
extern FMagmaContext *GMagmaContext;
void SuperSerialize(FArchive &Ar);

void Driver_14c280()
{
    Escape(&GMalloc);
    Escape(new FMagmaFactory());
}

void Driver_14c350(FArchive &Ar)
{
    Escape(&GMalloc);
    Escape(&GMagmaContext);
    SuperSerialize(Ar);
    GMagmaContext->Serialize(Ar);
}
