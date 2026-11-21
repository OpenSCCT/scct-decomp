// w4_item_0010.cpp -- Versus RVA 0x124a60-0x124ea0, AActor script natives
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
#define RESULT_DECL void *const Result

enum EName
{
    NAME_None = 0,
};

struct FName
{
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
};

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
};

class UObject;
class UProperty;
class UClass;
class UMesh;
class UMeshInstance;
class ULevel;
class AActor;
struct FFrame;

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];
extern BYTE *GPropAddr;
extern UObject *GPropObject;
extern UProperty *GProperty;
extern const FVector &GMath_UnitZ;

class UObject
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20();
    virtual void NetDirty(UProperty *Property);                     // +0x54
    virtual void Slot22(); virtual void Slot23(); virtual void Slot24(); virtual void Slot25();

    DWORD unk_04[6];
    DWORD ObjectFlags;              // 0x1c
    FName Name;                     // 0x20
    UClass *Class;                  // 0x24
};

struct FFrame
{
    void *VfTable;
    void *Node;                     // +0x04
    UObject *Object;                // +0x08
    BYTE *Code;                     // +0x0c

    __forceinline void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

class UMesh : public UObject
{
public:
    UMeshInstance *MeshGetInstance(const AActor *Actor);
};

class UMeshInstance : public UObject
{
public:
    virtual void Slot26(); virtual void Slot27(); virtual void Slot28(); virtual void Slot29();
    virtual void Slot30(); virtual void Slot31(); virtual void Slot32(); virtual void Slot33();
    virtual void Slot34(); virtual void Slot35(); virtual void Slot36(); virtual void Slot37();
    virtual void Slot38(); virtual void Slot39(); virtual void Slot40(); virtual void Slot41();
    virtual void Slot42(); virtual void Slot43(); virtual void Slot44(); virtual void Slot45();
    virtual void Slot46(); virtual void Slot47(); virtual void Slot48(); virtual void Slot49();
    virtual void Slot50(); virtual void Slot51(); virtual void Slot52(); virtual void Slot53();
    virtual void Slot54(); virtual void Slot55(); virtual void Slot56(); virtual void Slot57();
    virtual void Slot58();
    virtual FName GetActiveAnimSequence(INT Channel);               // +0xec
    virtual FLOAT GetActiveAnimRate(INT Channel);                   // +0xf0
    virtual FLOAT GetActiveAnimFrame(INT Channel);                  // +0xf4
};

class FCollisionHash
{
public:
    void AddActor(AActor *Actor);
};
void __stdcall FCollisionHash_RemoveActor(FCollisionHash *Hash, AActor *Actor);

class ULevel
{
public:
    BYTE unk_0000[0x3a48];
    FCollisionHash *Hash;           // 0x3a48
};

class AActor : public UObject
{
public:
    virtual UBOOL IsBlockedBy(const AActor *Other) const;           // +0x68 (slot 26)
    virtual void Slot27(); virtual void Slot28(); virtual void Slot29();
    virtual void Slot30(); virtual void Slot31(); virtual void Slot32(); virtual void Slot33();
    virtual void Slot34(); virtual void Slot35(); virtual void Slot36(); virtual void Slot37();
    virtual void Slot38(); virtual void Slot39(); virtual void Slot40(); virtual void Slot41();
    virtual void Slot42(); virtual void Slot43(); virtual void Slot44(); virtual void Slot45();
    virtual void Slot46();
    virtual void SetBase(AActor *NewBase, const FVector &NewFloor, UBOOL bNotifyActor); // +0xbc

    BYTE unk_028[0x1a4 - 0x28];
    ULevel *XLevel;                 // 0x1a4
    BYTE unk_1a8[0x1bc - 0x1a8];
    UMesh *Mesh;                    // 0x1bc
    BYTE unk_1c0[0x1d4 - 0x1c0];
    UMeshInstance *MeshInstance;    // 0x1d4
    BYTE unk_1d8[0x23c - 0x1d8];
    FLOAT DrawScale;                // 0x23c
    BYTE unk_240[0x268 - 0x240];
    FLOAT CollisionRadius;          // 0x268
    FLOAT CollisionHeight;          // 0x26c
    BYTE unk_270[0x2e8 - 0x270];
    DWORD unk_2e8 : 27;
    DWORD bOnlyAffectPawns : 1;     // 0x2e8 bit 27
    DWORD unk_2ec;                  // 0x2ec (bit 2: bNetDirty)
    DWORD unk_2f0 : 12;
    DWORD bCollideActors : 1;       // 0x2f0 bit 12
    DWORD unk_2f0_b13 : 1;
    DWORD bBlockActors : 1;         // 0x2f0 bit 14
    DWORD bBlockPlayers : 1;        // 0x2f0 bit 15

    void SetCollision(UBOOL NewCollideActors, UBOOL NewBlockActors, UBOOL NewBlockPlayers);
    void SetCollisionSize(FLOAT NewRadius, FLOAT NewHeight);
    void SetDrawScale(FLOAT NewScale);

    void execGetAnimParams(FFrame &Stack, RESULT_DECL);
    void execSetCollision(FFrame &Stack, RESULT_DECL);
    void execOnlyAffectPawns(FFrame &Stack, RESULT_DECL);
    void execSetCollisionSize(FFrame &Stack, RESULT_DECL);
    void execSetBase(FFrame &Stack, RESULT_DECL);
    void execSetDrawScale(FFrame &Stack, RESULT_DECL);
};

#define P_GET_INT(var)              INT var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_UBOOL(var)            UBOOL var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_UBOOL_OPTX(var, def)  UBOOL var = def; Stack.Step(Stack.Object, &var);
#define P_GET_FLOAT(var)            FLOAT var = 0.0f; Stack.Step(Stack.Object, &var);
#define P_GET_OBJECT(cls, var)      cls *var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_VECTOR_OPTX(var, def) FVector var = def; Stack.Step(Stack.Object, &var);
#define P_GET_NAME_REF(var)         FName var##T(NAME_None); GPropAddr = 0; \
    Stack.Step(Stack.Object, &var##T); \
    if (GPropObject) GPropObject->NetDirty(GProperty); \
    FName *var = GPropAddr ? (FName *)GPropAddr : &var##T;
#define P_GET_FLOAT_REF(var)        FLOAT var##T = 0.0f; GPropAddr = 0; \
    Stack.Step(Stack.Object, &var##T); \
    if (GPropObject) GPropObject->NetDirty(GProperty); \
    FLOAT *var = GPropAddr ? (FLOAT *)GPropAddr : &var##T;
#define P_FINISH                    Stack.Code++;

// AActor::execGetAnimParams (RVA 0x124a60)
void AActor::execGetAnimParams(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Channel);
    P_GET_NAME_REF(OutSeqName);
    P_GET_FLOAT_REF(OutAnimFrame);
    P_GET_FLOAT_REF(OutAnimRate);
    P_FINISH;
    *OutSeqName = NAME_None;
    *OutAnimFrame = 0.0f;
    *OutAnimRate = 0.0f;
    if (Mesh)
    {
        Mesh->MeshGetInstance(this);
        *OutSeqName = MeshInstance->GetActiveAnimSequence(Channel);
        *OutAnimFrame = MeshInstance->GetActiveAnimFrame(Channel);
        *OutAnimRate = MeshInstance->GetActiveAnimRate(Channel);
    }
}

// AActor::execSetCollision (RVA 0x124bf0)
void AActor::execSetCollision(FFrame &Stack, RESULT_DECL)
{
    P_GET_UBOOL_OPTX(bNewCollideActors, bCollideActors);
    P_GET_UBOOL_OPTX(bNewBlockActors, bBlockActors);
    P_GET_UBOOL_OPTX(bNewBlockPlayers, bBlockPlayers);
    P_FINISH;
    SetCollision(bNewCollideActors, bNewBlockActors, bNewBlockPlayers);
}

// AActor::execOnlyAffectPawns (RVA 0x124ca0)
void AActor::execOnlyAffectPawns(FFrame &Stack, RESULT_DECL)
{
    P_GET_UBOOL(bNewOnlyAffectPawns);
    P_FINISH;
    if (bCollideActors && bNewOnlyAffectPawns != bOnlyAffectPawns)
    {
        SetCollision(0, bBlockActors, bBlockPlayers);
        bOnlyAffectPawns = bNewOnlyAffectPawns;
        SetCollision(1, bBlockActors, bBlockPlayers);
    }
}

// AActor::execSetCollisionSize (RVA 0x124d50)
void AActor::execSetCollisionSize(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(NewRadius);
    P_GET_FLOAT(NewHeight);
    P_FINISH;
    SetCollisionSize(NewRadius, NewHeight);
    *(DWORD *)Result = 1;
}

// AActor::execSetBase (RVA 0x124dd0)
void AActor::execSetBase(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(AActor, NewBase);
    P_GET_VECTOR_OPTX(NewFloor, GMath_UnitZ);
    P_FINISH;
    SetBase(NewBase, NewFloor, 1);
}

// AActor::execSetDrawScale (RVA 0x124e60)
void AActor::execSetDrawScale(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(NewScale);
    P_FINISH;
    SetDrawScale(NewScale);
}

// Scaffolding for the LTCG link, not part of the unit.
// Callee stubs model the retail LTCG calling conventions of AActor::SetCollision
// (this in EDI, NewBlockPlayers in EAX, other args on stack), SetCollisionSize
// and SetDrawScale (this in EAX, float args on stack).
void Escape(const void *);

__declspec(noinline) void AActor::SetCollision(UBOOL NewCollideActors, UBOOL NewBlockActors,
                                               UBOOL NewBlockPlayers)
{
    if (bCollideActors && XLevel->Hash)
        FCollisionHash_RemoveActor(XLevel->Hash, this);
    Escape(&NewCollideActors);
    Escape(&NewBlockActors);
    bCollideActors = NewCollideActors;
    bBlockActors = NewBlockActors;
    bBlockPlayers = NewBlockPlayers;
    if (bCollideActors && XLevel->Hash)
        XLevel->Hash->AddActor(this);
    unk_2ec |= 4;
}

__declspec(noinline) void AActor::SetCollisionSize(FLOAT NewRadius, FLOAT NewHeight)
{
    CollisionRadius = NewRadius;
    CollisionHeight = NewHeight;
    unk_2ec |= 4;
}

__declspec(noinline) void AActor::SetDrawScale(FLOAT NewScale)
{
    DrawScale = NewScale;
    unk_2ec |= 4;
}

typedef void (AActor::*ActorNative)(FFrame &Stack, RESULT_DECL);
void Driver_124a60(ActorNative *Out)
{
    *Out = &AActor::execGetAnimParams;
    Escape(GNatives);
}
void Driver_124bf0(ActorNative *Out)
{
    *Out = &AActor::execSetCollision;
    Escape(GNatives);
}
void Driver_124ca0(ActorNative *Out)
{
    *Out = &AActor::execOnlyAffectPawns;
    Escape(GNatives);
}
void Driver_124d50(ActorNative *Out)
{
    *Out = &AActor::execSetCollisionSize;
    Escape(GNatives);
}
void Driver_124e60(ActorNative *Out)
{
    *Out = &AActor::execSetDrawScale;
    Escape(GNatives);
}
