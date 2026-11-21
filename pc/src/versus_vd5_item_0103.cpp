// Work item 0103 (w3): AMover key-position updates (RVA 0xafb90, 0xafc90)
// and small ASPawnAttaque controller queries (RVA 0xafda0..0xafe10).
// LTCG unit: FCollisionHash::AddActor takes the actor in EBX, and the two
// helpers at 0xafdf0 / 0xafe10 take their object in EAX.
// Field names follow UE2 movers (KeyNum, BasePos, BaseRot, KeyPos, KeyRot,
// Location, Rotation, XLevel) where the layout supports it; other fields
// use neutral offset names.

typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef float FLOAT;
typedef int INT;
typedef DWORD UBOOL;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
    FRotator() {}
    FRotator(INT InPitch, INT InYaw, INT InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}
    FRotator operator+(const FRotator &R) const { return FRotator(Pitch + R.Pitch, Yaw + R.Yaw, Roll + R.Roll); }
};

struct FBox { FVector Min, Max; };

template <class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

class AActor;

class FCollisionHash
{
public:
    void AddActor(AActor *Actor);       // retail 0x10a198a0 (LTCG: Actor in EBX)
};

// retail 0x10a19a20, FCollisionHash::RemoveActor (LTCG: hash and actor on the stack)
void __stdcall FCollisionHash_RemoveActor(FCollisionHash *Hash, AActor *Actor);

struct ULevel
{
    BYTE Pad[0x3a48];
    FCollisionHash *Hash;               // 0x3a48
};

class AActor
{
public:
    virtual void Vtbl0();
    BYTE     Pad004[0x80 - 0x4];
    FVector  Location;                  // 0x80
    BYTE     Pad08C[0xc8 - 0x8c];
    FBox     Box;                       // 0xc8
    FRotator Rotation;                  // 0xe0
    BYTE     Pad0EC[0x134 - 0xec];
    INT      F134;                      // 0x134
    BYTE     Pad138[0x1a4 - 0x138];
    ULevel  *XLevel;                    // 0x1a4
    BYTE     Pad1A8[0x1c4 - 0x1a8];
    INT     *F1C4;                      // 0x1c4
    INT      F1C8;                      // 0x1c8
    BYTE     Pad1CC[0x2f0 - 0x1cc];
    DWORD    Flags2F0Lo : 6;            // 0x2f0
    DWORD    bF2F0_40 : 1;              // 0x2f0 bit 6
    DWORD    Flags2F0Mid : 5;
    DWORD    bCollideActors : 1;        // 0x2f0 bit 12
    DWORD    Flags2F0Hi : 19;
};

// Global pointer read by the mover reset (retail 0x10ccacc0).
extern FVector *GUnnamedVector_ccacc0;

class AMover : public AActor
{
public:
    BYTE     Pad2F4[0x31c - 0x2f4];
    FVector  KeyPos[8];                 // 0x31c
    FVector  BasePos;                   // 0x37c
    BYTE     Pad388[0x3a0 - 0x388];
    FVector  Vec3A0;                    // 0x3a0
    FRotator KeyRot[8];                 // 0x3ac
    FRotator BaseRot;                   // 0x40c
    BYTE     Pad418[0x424 - 0x418];
    FRotator Rot424;                    // 0x424
    BYTE     Pad430[0x4df - 0x430];
    BYTE     Key4DF;                    // 0x4df
    BYTE     Pad4E0[0x4e3 - 0x4e0];
    BYTE     KeyNum;                    // 0x4e3

    virtual void Reset_afc90();         // AMover vtable[33]
    virtual void PostEditChange_afb90();// AMover vtable[79]
};

// RVA 0xafb90 (AMover vtable[79]); near: 15 bytes, x87 operand order of Location.Y/Z and rotation load order differ
void AMover::PostEditChange_afb90()
{
    KeyNum = Clamp((INT)KeyNum, 0, 7);
    if (bCollideActors && XLevel->Hash)
        FCollisionHash_RemoveActor(XLevel->Hash, this);
    Location = BasePos + KeyPos[KeyNum];
    Rotation = BaseRot + KeyRot[KeyNum];
    if (bCollideActors && XLevel->Hash)
        XLevel->Hash->AddActor(this);
}

// RVA 0xafc90 (AMover vtable[33]); near: 15 bytes, x87 operand order of Location.Y/Z differs
void AMover::Reset_afc90()
{
    if (bCollideActors && XLevel->Hash)
        FCollisionHash_RemoveActor(XLevel->Hash, this);
    Location = KeyPos[Key4DF] + BasePos;
    Rotation = BaseRot + KeyRot[Key4DF];
    if (bCollideActors && XLevel->Hash)
        XLevel->Hash->AddActor(this);
    Vec3A0 = *GUnnamedVector_ccacc0;
    Rot424 = FRotator(0, 0, 0);
}

// Object held at ASPawnAttaque+0x38c (likely the Controller; neutral name).
class UnnamedHeld_38c
{
public:
    virtual void Vtbl0();
    BYTE  Pad004[0x2f6 - 0x4];
    BYTE  Flags2F6;                     // 0x2f6
    BYTE  Pad2F7[0x310 - 0x2f7];
    BYTE  Flags310;                     // 0x310
    BYTE  Pad311[0x4a4 - 0x311];
    INT   Field4A4;                     // 0x4a4
};

// Same object seen through its vtable; only slot 80 (offset 0x140) is used.
class UnnamedVirtual_38c
{
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
    virtual void Slot04();
    virtual void Slot05();
    virtual void Slot06();
    virtual void Slot07();
    virtual void Slot08();
    virtual void Slot09();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual void Slot23();
    virtual void Slot24();
    virtual void Slot25();
    virtual void Slot26();
    virtual void Slot27();
    virtual void Slot28();
    virtual void Slot29();
    virtual void Slot30();
    virtual void Slot31();
    virtual void Slot32();
    virtual void Slot33();
    virtual void Slot34();
    virtual void Slot35();
    virtual void Slot36();
    virtual void Slot37();
    virtual void Slot38();
    virtual void Slot39();
    virtual void Slot40();
    virtual void Slot41();
    virtual void Slot42();
    virtual void Slot43();
    virtual void Slot44();
    virtual void Slot45();
    virtual void Slot46();
    virtual void Slot47();
    virtual void Slot48();
    virtual void Slot49();
    virtual void Slot50();
    virtual void Slot51();
    virtual void Slot52();
    virtual void Slot53();
    virtual void Slot54();
    virtual void Slot55();
    virtual void Slot56();
    virtual void Slot57();
    virtual void Slot58();
    virtual void Slot59();
    virtual void Slot60();
    virtual void Slot61();
    virtual void Slot62();
    virtual void Slot63();
    virtual void Slot64();
    virtual void Slot65();
    virtual void Slot66();
    virtual void Slot67();
    virtual void Slot68();
    virtual void Slot69();
    virtual void Slot70();
    virtual void Slot71();
    virtual void Slot72();
    virtual void Slot73();
    virtual void Slot74();
    virtual void Slot75();
    virtual void Slot76();
    virtual void Slot77();
    virtual void Slot78();
    virtual void Slot79();
    virtual UBOOL Query140();           // vtable slot 80, offset 0x140
};

class ASPawnAttaque
{
public:
    virtual void Vtbl0();
    BYTE Pad004[0x38c - 0x4];
    UnnamedHeld_38c *Held;              // 0x38c

    virtual ASPawnAttaque *Query_afda0();   // vtable[24]
    virtual UBOOL Query_afdd0();            // vtable[25]
    __declspec(noinline) UBOOL Query_afdf0();
    __declspec(noinline) UBOOL Query_afe10();
};

// RVA 0xafda0 (ASPawnAttaque vtable[24])
ASPawnAttaque *ASPawnAttaque::Query_afda0()
{
    if (Held && (Held->Flags2F6 & 1))
        return Held->Field4A4 ? this : 0;
    return 0;
}

// RVA 0xafdd0 (ASPawnAttaque vtable[25])
UBOOL ASPawnAttaque::Query_afdd0()
{
    if (Held && (Held->Flags310 & 1))
        return 1;
    return 0;
}

// RVA 0xafdf0 (LTCG: this in EAX)
UBOOL ASPawnAttaque::Query_afdf0()
{
    if (Held && (Held->Flags2F6 & 1))
        return 1;
    return 0;
}

// RVA 0xafe10 (LTCG: this in EAX)
UBOOL ASPawnAttaque::Query_afe10()
{
    UnnamedVirtual_38c *V = (UnnamedVirtual_38c *)Held;
    if (V && V->Query140())
        return 1;
    return 0;
}

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit: a stand-in body for the
// retail AddActor so the linker gives it retail's register convention, and
// drivers calling the functions the way retail callers do.

FBox *UnnamedBox(AActor *Actor, FBox *Out);
FBox *UnnamedExpand(FBox *In, FBox *Out, FLOAT By);
void UnnamedInsert(FCollisionHash *Hash, AActor *Actor, INT X);

__declspec(noinline) void FCollisionHash::AddActor(AActor *Actor)
{
    FBox Tmp, Tmp2;
    if (!Actor || Actor->bF2F0_40)
        return;
    if (Actor->F134 > 0)
        FCollisionHash_RemoveActor(this, Actor);
    Actor->Box = *UnnamedBox(Actor, &Tmp);
    Actor->Box = *UnnamedExpand(&Actor->Box, &Tmp2, 4.2f);
    for (INT i = 0; i < Actor->F1C8; i++)
        UnnamedInsert(this, Actor, Actor->F1C4[i]);
}

void Escape(void *);
void Driver_afb90(AMover *A, AMover *B) { A->AMover::PostEditChange_afb90(); B->AMover::PostEditChange_afb90(); }
void Driver_afc90(AMover *A, AMover *B) { Escape(&GUnnamedVector_ccacc0); A->AMover::Reset_afc90(); B->AMover::Reset_afc90(); }
void Driver_afda0(ASPawnAttaque *A) { Escape(A->ASPawnAttaque::Query_afda0()); Escape((void *)A->ASPawnAttaque::Query_afdd0()); }
void Driver_afdf0(ASPawnAttaque *A, ASPawnAttaque *B) { Escape((void *)A->Query_afdf0()); Escape((void *)B->Query_afdf0()); }
void Driver_afe10(ASPawnAttaque *A, ASPawnAttaque *B) { Escape((void *)A->Query_afe10()); Escape((void *)B->Query_afe10()); }
