// Work item w3 0109: Versus RVA 0xb3890, UMeshAnimation::PostLoad (vtable slot 8).
// LTCG unit (VC7.0 /GL, /LTCG). UObject::PostLoad is inlined: it sets
// RF_DebugPostLoad and loads per-object localized properties (LoadLocalized,
// retail 0x16f70, this in ESI). Each move (MotionChunk, 0x2c bytes) then fixes
// up its animation tracks against the outer package (retail 0xdf5e0, this in EDI,
// one stack argument, ret 4).
// The callees are defined below only so the link gives them their retail
// conventions; they are matched separately and are not part of this unit.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

enum { RF_PerObjectLocalized = 0x00000100, RF_DebugPostLoad = 0x20000000 };

class UObject;

template <class T> class TArray
{
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

class UObject
{
public:
    virtual ~UObject();
    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;          // 0x18
    DWORD ObjectFlags;       // 0x1c
    INT Name;                // 0x20
    void *Class;             // 0x24

    virtual void PostLoad();
    void LoadLocalized();
};

struct FTrackEntry
{
    INT A;
    UObject *Pending;
    UObject *Resolved;
};

// 0x2c bytes; tracks at +0x1c.
struct MotionChunk
{
    INT Pad[7];
    TArray<FTrackEntry> Tracks;     // 0x1c
    INT Pad2[1];

    void Fixup(UObject *InOuter);
};

class UMeshAnimation : public UObject
{
public:
    INT Pad28[7];                   // 0x28
    TArray<MotionChunk> Moves;      // 0x44

    virtual void PostLoad();
};

void UMeshAnimation::PostLoad()
{
    ObjectFlags |= RF_DebugPostLoad;
    if (ObjectFlags & RF_PerObjectLocalized)
        LoadLocalized();
    for (INT i = 0; i < Moves.Num(); i++)
        Moves(i).Fixup(Outer);
}

// ---- Stand-in callee bodies (retail 0x16f70 and 0xdf5e0), not part of the unit ----
struct FName { INT Index; };
struct UClassLite { INT Pad[34]; DWORD ClassFlags; UObject *ClassOuter; };
const TCHAR *GetLocalizedPackageName(INT Name);
void LoadLocalizedStruct(void *Struct, const TCHAR *IntName, INT Prefix, INT SectionName, INT KeyPrefix, void *Data);
void UObject::LoadLocalized()
{
    UClassLite *Cls = (UClassLite *)Class;
    if (!(Cls->ClassFlags & 0x200))
        return;
    if (Index != -1 && (ObjectFlags & RF_PerObjectLocalized) && Outer->Outer)
    {
        const TCHAR *IntName = GetLocalizedPackageName(Outer->Outer->Name);
        LoadLocalizedStruct(Cls, IntName, 0, Outer->Name, Name, this);
    }
    else
    {
        const TCHAR *IntName = GetLocalizedPackageName((Index == -1 ? Cls->ClassOuter : Outer)->Name);
        INT Section = Index == -1 ? 0 : Name;
        LoadLocalizedStruct(Cls, IntName, 0, Section, 0, this);
    }
}

class UClass;
class FOutputDevice;
extern UClass TrackClass;                    // 0x10cc1220
extern void (*TrackClass_ClassConstructor)(void *);   // field of TrackClass, 0x10cc1324
extern UObject *GObjTransientPkg;            // 0x10c925b4
extern FOutputDevice *GError;                // 0x10c71aa8
UObject *StaticConstructObject(UClass *Class, UObject *InOuter, INT Name, DWORD SetFlags, UObject *Template, FOutputDevice *Error, UObject *SubObjectRoot, UObject *SubObjectOuter);
struct FTrackObject { INT Pad[11]; UObject *Source; };
void MotionChunk::Fixup(UObject *InOuter)
{
    for (INT i = 0; i < Tracks.Num(); i++)
    {
        if (Tracks(i).Pending)
        {
            UObject *O = StaticConstructObject(&TrackClass, InOuter == (UObject *)-1 ? GObjTransientPkg : InOuter, 0, 4, 0, GError, 0, 0);
            if (O)
                TrackClass_ClassConstructor(O);
            ((FTrackObject *)O)->Source = Tracks(i).Pending;
            Tracks(i).Resolved = O;
            Tracks(i).Pending = 0;
        }
    }
}

// ---- Scaffolding for the link, not part of the unit ----
void Escape(void *);
void Driver_b3890(UMeshAnimation *A)
{
    // Retail reaches PostLoad through the vtable, so its address is taken.
    void (UMeshAnimation::*Fn)() = &UMeshAnimation::PostLoad;
    Escape(&Fn);
    A->UMeshAnimation::PostLoad();
}
