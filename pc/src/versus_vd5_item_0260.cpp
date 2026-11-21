// ULevel::Destroy (Versus RVA 0xf6390, ULevel vtable slot 9), UnLevel.cpp.
// The object was built with VC7.0 /GL and linked with /LTCG: the projector
// detach helper (retail 0xc9830) takes its render info in EBX and a flag in EAX.
// Member names other than Unreal's own are neutral (Field_<offset>).
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned short TCHAR;
typedef unsigned char BYTE;
typedef float FLOAT;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;
inline void operator delete(void *Ptr) { GMalloc->Free(Ptr); }

template <class T> struct TArray {
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

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
};

class ULevel;
struct FProjectorPrimitive;

// Reference-counted projector render info (UnProjector.cpp).
struct ALevelInfo_Stub { BYTE Pad[0x3b0]; FLOAT TimeSeconds; };
struct AProjector_Stub { BYTE Pad[0x1a0]; ALevelInfo_Stub *Level; };
struct FProjectorRenderInfo {
    AProjector_Stub *Projector;
    INT ReferenceCount;
    DWORD Field_08;
    DWORD Field_0C;
    double Field_10;
    void RemoveReference()
    {
        if (--ReferenceCount == 0)
            delete this;
    }
};

// Octree node (0x10 bytes) released recursively by retail 0x118440 / 0x1183c0.
struct FOctreeNode {
    TArray<void *> Items;
    FOctreeNode *Children;
    void RemoveAllActors(void *Tree);   // 0x118440
    ~FOctreeNode();                     // 0x1183c0
};
struct FCollisionOctree {
    FOctreeNode *RootNode;
    ~FCollisionOctree()
    {
        RootNode->RemoveAllActors(this);
        delete RootNode;
    }
};

// Polymorphic helper owned at 0xec, released through its virtual destructor (slot 3).
class FLevelHelper_EC {
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual ~FLevelHelper_EC();
};

// Global cleared by retail 0x112e60 (a stack-this member after LTCG).
struct FGlobal_CA7068;
extern FGlobal_CA7068 GGlobal_CA7068;
void __stdcall ClearGlobal_112e60(FGlobal_CA7068 *G);

void __stdcall DetachProjector(FProjectorRenderInfo *Info, ULevel *Level, UBOOL bClear, UBOOL bStatic);

class ULevelBase : public UObject {
};

class ULevel : public ULevelBase {
public:
    BYTE Pad04[0xec - 4];
    FLevelHelper_EC *Field_EC;
    BYTE PadF0[0x190 - 0xf0];
    double TimeSeconds_190;
    BYTE Pad198[0x3a48 - 0x198];
    FCollisionOctree *Field_3A48;
    BYTE Pad3A4C[0x4ab0 - 0x3a4c];
    TArray<FProjectorRenderInfo *> DynamicProjectors;
    union { TArray<FProjectorRenderInfo *> Projectors_4ABC; TArray<TArray<FProjectorPrimitive *> *> Primitives_4ABC; };
    TArray<TArray<FProjectorRenderInfo *> *> Projectors_4AC8;
    double Field_4AD4;
    virtual void Destroy();
};

void ULevel::Destroy()
{
    if (Field_3A48) {
        delete Field_3A48;
        Field_3A48 = 0;
    }
    for (INT i = 0; i < DynamicProjectors.Num(); i++) {
        DynamicProjectors(i)->RemoveReference();
        DetachProjector(DynamicProjectors(i), this, 1, 0);
    }
    ClearGlobal_112e60(&GGlobal_CA7068);
    if (Field_EC) {
        delete Field_EC;
        Field_EC = 0;
    }
    ULevelBase::Destroy();
}

// Scaffolding for the LTCG link, not part of the unit: a reduced stand-in for
// the projector detach helper (retail 0xc9830, UnProjector.cpp) so the linker
// gives it its register convention (render info in EBX, bClear in EAX).
void RemoveItem(void *Array, INT Index, INT Count, INT ElementSize);
struct FProjectorPrimitive { FProjectorRenderInfo *Info; ~FProjectorPrimitive(); };
void RemoveFromSet(void *Set, FProjectorRenderInfo **Key);
__declspec(noinline) void __stdcall DetachProjector(FProjectorRenderInfo *Info, ULevel *Level, UBOOL bClear, UBOOL bStatic)
{
    if (bClear) {
        Info->Field_08 = 0;
        Info->Field_0C = 0;
    } else {
        Info->Field_10 = Level->TimeSeconds_190 != 0.0 ? Info->Projector->Level->TimeSeconds : -1.0f;
    }
    if (!bStatic) {
        for (INT i = 0; i < Level->Primitives_4ABC.Num(); i++) {
            TArray<FProjectorPrimitive *> *List = Level->Primitives_4ABC(i);
            UBOOL AllMine = 1;
            for (INT j = 0; j < List->Num(); j++) {
                if ((*List)(j)->Info == Info) {
                    delete (*List)(j);
                    RemoveItem(List, j, 1, 4);
                    Info->RemoveReference();
                    while (j < List->Num()) {
                        FProjectorPrimitive *Prim = (*List)(j);
                        if (Prim->Info != Info) {
                            AllMine = 0;
                            break;
                        }
                        delete Prim;
                        RemoveItem(List, j, 1, 4);
                        Info->RemoveReference();
                    }
                    break;
                }
                AllMine = 0;
            }
            if (AllMine) {
                Level->Primitives_4ABC(i) = Level->Primitives_4ABC(Level->Primitives_4ABC.Num() - 1);
                RemoveItem(&Level->Primitives_4ABC, Level->Primitives_4ABC.Num() - 1, 1, 4);
                i--;
            }
        }
        for (INT k = 0; k < Level->Projectors_4AC8.Num(); k++) {
            TArray<FProjectorRenderInfo *> *L = Level->Projectors_4AC8(k);
            for (INT j = 0; j < L->Num(); j++) {
                if ((*L)(j) == Info) {
                    RemoveItem(L, j, 1, 4);
                    Info->RemoveReference();
                    break;
                }
            }
            if (L->Num() == 0) {
                Level->Projectors_4AC8(k) = Level->Projectors_4AC8(Level->Projectors_4AC8.Num() - 1);
                RemoveItem(&Level->Projectors_4AC8, Level->Projectors_4AC8.Num() - 1, 1, 4);
                k--;
            }
        }
    } else {
        Info->RemoveReference();
        FProjectorRenderInfo *Key = Info;
        RemoveFromSet(&Level->Field_4AD4, &Key);
    }
    Info->Projector = 0;
    Info->RemoveReference();
}
