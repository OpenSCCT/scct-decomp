// Work item 0108: UObject::ResetLoaders (0x1b6c0) and
// FArchiveSaveTagExports::operator<<(UObject*&) (0x1b7f0).
// Names follow Unreal Engine 2's UnObj.cpp / UnLinker.cpp; the layout offsets
// are taken from the retail code.

typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef unsigned short _WORD;

#define INDEX_NONE (-1)

enum EObjectFlags
{
    RF_TagExp         = 0x00000010,
    RF_Transient      = 0x00004000,
    RF_LoadForClient  = 0x00010000,
    RF_LoadForServer  = 0x00020000,
    RF_LoadForEdit    = 0x00040000,
    RF_NotForClient   = 0x00100000,
    RF_NotForServer   = 0x00200000,
    RF_NotForEdit     = 0x00400000,
};

enum { CLASS_RuntimeStatic = 0x80 };

class UObject;
class UClass;
class ULinkerLoad;
class FArchive;

template<class T> struct TArray
{
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

class UObject
{
public:
    virtual void Vf0();
    virtual void Vf1();
    virtual void Vf2();
    virtual ~UObject();
    virtual void Vf4();
    virtual void Vf5();
    virtual void Vf6();
    virtual void Vf7();
    virtual void Vf8();
    virtual void Vf9();
    virtual void Serialize(FArchive &Ar);   // slot 10 (+0x28)

    INT          Index;          // 0x04
    UObject     *HashNext;       // 0x08
    void        *StateFrame;     // 0x0c
    ULinkerLoad *_Linker;        // 0x10
    INT          _LinkerIndex;   // 0x14
    UObject     *Outer;          // 0x18
    DWORD        ObjectFlags;    // 0x1c
    INT          Name;           // 0x20
    UClass      *Class;          // 0x24

    UObject *GetOuter() const { return Outer; }
    UClass *GetClass() const { return Class; }
    DWORD GetFlags() const { return ObjectFlags; }
    void SetFlags(DWORD NewFlags) { ObjectFlags |= NewFlags; }
    UBOOL IsIn(UObject *SomeOuter) const
    {
        for (UObject *It = GetOuter(); It; It = It->GetOuter())
            if (It == SomeOuter)
                return 1;
        return SomeOuter == 0;
    }
    inline void SetLinker(ULinkerLoad *L, INT I);

    static TArray<UObject *> GObjLoaders;
    static void ResetLoaders(UObject *Pkg, UBOOL DynamicOnly, UBOOL ForceLazyLoad);
};

class UClass : public UObject
{
public:
    BYTE Pad[0x88 - 0x28];
    DWORD ClassFlags;            // 0x88
};

struct FObjectImport
{
    BYTE         Pad0[0x0a];
    _WORD        SourceIndex;    // 0x0a
    BYTE         Pad1[0x14 - 0x0c];
    ULinkerLoad *SourceLinker;   // 0x14
};

struct FObjectExport
{
    BYTE     Pad[0x14];
    UObject *_Object;            // 0x14
    BYTE     Pad1[0x1c - 0x18];
};

class FArchive;

struct FLazyLoader
{
    virtual void Load();
    FArchive *SavedAr;   // 0x04
    INT       SavedPos;  // 0x08
};

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const unsigned short *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const unsigned short *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class ULinkerLoad : public UObject
{
public:
    UObject *LinkerRoot;                 // 0x28
    BYTE     Pad[0x78 - 0x2c];
    TArray<FObjectImport> ImportMap;     // 0x78
    TArray<FObjectExport> ExportMap;     // 0x84
    BYTE     Pad2[0x4ec - 0x90];
    TArray<FLazyLoader *> LazyLoaders;   // 0x4ec

    void DetachAllLazyLoaders(UBOOL Load);
};

// ULinkerLoad::DetachAllLazyLoaders lives at RVA 0x59730 in retail (a separate
// LTCG unit that takes `this` in ESI); it is defined here so the link gives it
// the same register convention when ResetLoaders calls it.
void ULinkerLoad::DetachAllLazyLoaders(UBOOL Load)
{
    for (INT i = 0; i < LazyLoaders.Num(); i++)
    {
        FLazyLoader *LazyLoader = LazyLoaders(i);
        if (Load)
            LazyLoader->Load();
        LazyLoader->SavedAr = 0;
        LazyLoader->SavedPos = 0;
    }
    LazyLoaders.ArrayNum = 0;
    if (LazyLoaders.Data)
    {
        GMalloc->Free(LazyLoaders.Data);
        LazyLoaders.Data = 0;
        LazyLoaders.ArrayMax = 0;
    }
}


inline void UObject::SetLinker(ULinkerLoad *L, INT I)
{
    if (_Linker)
        _Linker->ExportMap(_LinkerIndex)._Object = 0;
    _Linker = L;
    _LinkerIndex = I;
}

void UObject::ResetLoaders(UObject *Pkg, UBOOL DynamicOnly, UBOOL ForceLazyLoad)
{
    for (INT i = GObjLoaders.Num() - 1; i >= 0; i--)
    {
        ULinkerLoad *Linker = (ULinkerLoad *)GObjLoaders(i);
        if (Pkg == 0 || Linker->LinkerRoot == Pkg)
        {
            if (DynamicOnly)
            {
                for (INT j = 0; j < Linker->ExportMap.Num(); j++)
                {
                    UObject *&Object = Linker->ExportMap(j)._Object;
                    if (Object && !(Object->GetClass()->ClassFlags & CLASS_RuntimeStatic))
                        Object->SetLinker(0, INDEX_NONE);
                }
            }
            else if (ForceLazyLoad)
            {
                Linker->DetachAllLazyLoaders(1);
            }
        }
        else
        {
            for (INT j = 0; j < Linker->ImportMap.Num(); j++)
            {
                ULinkerLoad *&Source = Linker->ImportMap(j).SourceLinker;
                if (Source && Source->LinkerRoot == Pkg)
                {
                    Source = 0;
                    Linker->ImportMap(j).SourceIndex = (_WORD)INDEX_NONE;
                }
            }
        }
    }
    if (!DynamicOnly)
    {
        for (INT i = GObjLoaders.Num() - 1; i >= 0; i--)
        {
            ULinkerLoad *Linker = (ULinkerLoad *)GObjLoaders(i);
            if (Pkg == 0 || Linker->LinkerRoot == Pkg)
                delete Linker;
        }
    }
}

class FArchive
{
public:
    virtual void Vf0();
    virtual void Vf1();
    virtual void Vf2();
    virtual void Vf3();
    virtual void Vf4();
    virtual void Vf5();
    virtual FArchive &operator<<(UObject *&Res);   // slot 6 (+0x18)
    BYTE Pad[0x40 - 4];
};

class FArchiveSaveTagExports : public FArchive
{
public:
    UObject *Parent;     // 0x40
    FArchive &operator<<(UObject *&Obj);
};

FArchive &FArchiveSaveTagExports::operator<<(UObject *&Obj)
{
    if (Obj && Obj->IsIn(Parent) && !(Obj->GetFlags() & (RF_Transient | RF_TagExp)))
    {
        Obj->SetFlags(RF_TagExp);
        if (!(Obj->GetFlags() & RF_NotForEdit))   Obj->SetFlags(RF_LoadForEdit);
        if (!(Obj->GetFlags() & RF_NotForClient)) Obj->SetFlags(RF_LoadForClient);
        if (!(Obj->GetFlags() & RF_NotForServer)) Obj->SetFlags(RF_LoadForServer);

        UObject *Class = (UObject *)Obj->GetClass();
        UObject *Outer = Obj->GetOuter();
        *(FArchive *)this << Class << Outer;

        Obj->Serialize(*this);
    }
    return *this;
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Driver_1b6c0(UObject *Pkg, UBOOL DynamicOnly, UBOOL ForceLazyLoad)
{
    Escape(&UObject::GObjLoaders);
    Escape(&GMalloc);
    UObject::ResetLoaders(Pkg, DynamicOnly, ForceLazyLoad);
}
