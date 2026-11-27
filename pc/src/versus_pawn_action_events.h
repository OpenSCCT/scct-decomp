// versus_pawn_action_events.h -- Versus pawn action, event, and script lookup types.
#ifndef VERSUS_PAWN_ACTION_EVENTS_H
#define VERSUS_PAWN_ACTION_EVENTS_H

#include "versus_build.h"
#include "unreal_types.h"
#include "unreal_math.h"
#include "unreal_containers.h"

enum EName {
#define REGISTER_NAME(symbol, index, flags, text) NAME_##symbol = index,
#include "versus_hardcoded_names.inl"
#undef REGISTER_NAME
};

class FName {
public:
    INT Index;
    FName() {}
    INT GetIndex() const { return Index; }
    UBOOL operator==(const FName &Other) const { return Index == Other.Index; }
    FName(EName Name) : Index(Name) {}
};

class UFunction;
class AActor;
class AController;
struct FGuid;

class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *Text, EName Event) = 0;
};
struct FFrame : public FOutputDevice {
    class UStruct *Node;
    class UObject *Object;
    BYTE *Code;
    BYTE *Locals;
};

class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown {
public:
    virtual ~UObject();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result);
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();

    UObject *FindInStateOrClass(FName InName, INT Global);
    UFunction *FindFunctionChecked(FName InName, INT Global);
    INT Index;
    BYTE unk_8[4];
    struct FStateFrame *StateFrame;
    BYTE unk_10[12];
    DWORD ObjectFlags;
    FName Name;
    class UClass *Class;
};

class AActor : public UObject {
public:
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();
    virtual void VirtualSlot44();
    virtual void VirtualSlot45();
    virtual void VirtualSlot46();
    virtual void VirtualSlot47();
    virtual void VirtualSlot48();
    virtual void VirtualSlot49();
    virtual void VirtualSlot50();
    virtual void VirtualSlot51();
    virtual void VirtualSlot52();
    virtual void VirtualSlot53();
    virtual void VirtualSlot54();
    virtual void VirtualSlot55();
    virtual void VirtualSlot56();
    virtual void VirtualSlot57();
    virtual void VirtualSlot58();
    virtual void VirtualSlot59();
    virtual void VirtualSlot60();
    virtual void VirtualSlot61();
    virtual void VirtualSlot62();
    virtual void setPhysics(BYTE NewPhysics, AActor *NewFloor, const FVector &FloorNormal);
    virtual void VirtualSlot64();
    virtual void VirtualSlot65();
    virtual void VirtualSlot66();
    virtual void VirtualSlot67();
    virtual void VirtualSlot68();
    virtual void VirtualSlot69();
    virtual void VirtualSlot70();
    virtual void VirtualSlot71();
    virtual void VirtualSlot72();
    virtual void PlayAnim(INT Channel, FName Sequence, FLOAT Rate = 1.f, FLOAT TweenTime = .1f,
                          UBOOL bLoop = 0, UBOOL bBackwards = 0, UBOOL bContinueAtFrame = 0,
                          INT Extra = 0);
    virtual void VirtualSlot74();
    virtual void VirtualSlot75();
    virtual void VirtualSlot76();
    virtual void VirtualSlot77();

    BYTE unk_28[0xbc - 0x28];
    FVector PrePivot;
    BYTE unk_c8[0xe0 - 0xc8];
    FRotator Rotation;
    BYTE unk_ec[0x1a4 - 0xec];
    class ULevel *XLevel;
    BYTE unk_1a8[0x268 - 0x1a8];
    FLOAT CollisionRadius;
    FLOAT CollisionHeight;
    BYTE unk_270[0x2de - 0x270];
    BYTE Role;
    BYTE unk_2df[0x2f0 - 0x2df];
    BITFIELD unk_2f0_0 : 13;
    BITFIELD bCollideWorld : 1;
    BITFIELD unk_2f0_14 : 18;
    BYTE unk_2f4[4];

    void SetCollision(UBOOL CollideActors, UBOOL BlockActors, UBOOL BlockPlayers);
    class ULevel *GetLevel() const { return XLevel; }
    void SetCollisionSize(FLOAT NewRadius, FLOAT NewHeight);
    void FadeChannels(INT Start, INT End, FLOAT Amount);
};

class AController : public AActor {
public:
    virtual void VirtualSlot78();
    virtual void VirtualSlot79();
    virtual UBOOL IsLocalPlayerController();
    virtual void VirtualSlot81();
    virtual void VirtualSlot82();

    BYTE unk_2f8[0x3c4 - 0x2f8];
};

class APlayerController : public AController {
public:
    virtual void VirtualSlot83();
    BYTE unk_3c4[0x604 - 0x3c4];
};

class ASPlayerController : public APlayerController {
public:
    void eventClientStopRM(INT TheAction);
    BYTE unk_604[0xc70 - 0x604];
};

class APawn : public AActor {
public:
    virtual void VirtualSlot78();
    virtual void VirtualSlot79();
    virtual void VirtualSlot80();
    virtual void Crouch(UBOOL bClientSimulation);
    virtual void VirtualSlot82();
    virtual void VirtualSlot83();

    BYTE unk_2f8[0x38c - 0x2f8];
    AController *Controller;
    BYTE unk_390[0x400 - 0x390];
    FLOAT CrouchHeight;
    FLOAT CrouchRadius;
    BYTE unk_408[0x480 - 0x408];
    FLOAT BlendChangeTime;
    BYTE unk_484[0x4a8 - 0x484];
    BITFIELD initSlowReplication : 1;
    BITFIELD unk_4a8_b1 : 4;
    BITFIELD bIsCrouched : 1;
    BITFIELD unk_4a8_b6 : 26;
    BYTE unk_4ac[4];
};

enum PawnType { SPAWNOFFENSE, SPAWNDEFENSE };
enum IK_Type_ { IKT_WEAPONLOADED, IKT_NONE, IKT_GRAB_FIREMODE, IKT_BTW, IKT_PIPH, IKT_JCVD };

class ASBasePawn : public APawn {
public:
    BYTE unk_4b0[0x4bc - 0x4b0];
    FVector vMoveAfterRM;
    BYTE unk_4c8[0x62c - 0x4c8];
    class ASBasePawn *m_AttackTarget;
    ASBasePawn *m_AttackedBy;
    BYTE unk_634[0x644 - 0x634];
    INT rRotAfterRM;
    BYTE unk_648[0x718 - 0x648];
    BYTE IK_Type;
    BYTE unk_719[2];
    BYTE IK_TypeBeforeDamage;
    BYTE unk_71c[0x8b4 - 0x71c];
    FName ADeathStForward;
    FName ADeathStBack;
    FName ADeathStLeft;
    FName ADeathStRight;
    FName ADeathStDown;
    FName ADeathCrForward;
    FName ADeathCrBack;
    FName ADeathCrLeft;
    FName ADeathCrRight;
    FName ADeathCrDown;
    FName ADeathStForward2H;
    FName ADeathStBack2H;
    FName ADeathStLeft2H;
    FName ADeathStRight2H;
    FName ADeathStDown2H;
    FName ADeathCrForward2H;
    FName ADeathCrBack2H;
    FName ADeathCrLeft2H;
    FName ADeathCrRight2H;
    FName ADeathCrDown2H;
    BYTE unk_904[0xa48 - 0x904];
    FLOAT fBlendTimeWithC0;
    BYTE unk_a4c[0xaac - 0xa4c];
    FLOAT fTimeOfFeetLedge;
    BYTE unk_ab0[2];
    BYTE ZoneConfig;
    BYTE ZoneConfigForClient;
    BYTE unk_ab4[0xad8 - 0xab4];
    BYTE PipHFire;
    BYTE BTW;
    BYTE unk_ada;
    BYTE SPawnType;
    BYTE unk_adc[0xaf0 - 0xadc];
    BITFIELD unk_af0_0 : 14;
    BITFIELD bLyingOnGround : 1;
    BITFIELD bNoRunAnimation : 1;
    BITFIELD unk_af0_16 : 3;
    BITFIELD bIsRolling : 1;
    BITFIELD unk_af0_20 : 6;
    BITFIELD bBeginSpecial12Anim : 1;
    BITFIELD unk_af0_27 : 2;
    BITFIELD bWeaponTransit : 1;
    BITFIELD unk_af0_30 : 2;
    BYTE unk_af4[0xb60 - 0xaf4];

    virtual void Crouch(UBOOL bClientSimulation);
    void eventStartCrouch(FLOAT HeightAdjust);
    BYTE StartActionRootMotion(INT Action, FVector MoveAfter, FLOAT Yaw);
    INT CheckLedgeGrab(BYTE Mode);
    void ReinitBecauseOfDivergences();
    void execReinitBecauseOfDivergences(struct FFrame &Stack, void *const Result);
    void PlayWalkingAction(INT Action);
    void eventEvSetWeaponLoaded(INT num);
    void PlayDeathAnimation(INT Direction);
};

APlayerController *GetTopOwner(AActor *Actor);
extern const FVector &GMath_UnitZ;
extern UBOOL GScriptFunctionLookupEnabled; // Descriptive name for the gate read at 0x10c968f0.

struct FFieldHashEntry {
    UObject *Field;
    INT Next;
};

struct FFieldHash {
    INT HashCount;
    FFieldHashEntry *Entries;
};

class UField : public UObject {
public:
    UField *SuperField;
    UField *Next;
};

class UStruct : public UField {
public:
    BYTE unk_30[0x68 - 0x30];
};

class UState : public UStruct {
public:
    BYTE unk_68[0x80 - 0x68];
    FFieldHash FieldHash;
};

class UClass : public UState {
public:
    DWORD ClassCastFlags;
    BYTE unk_8c[0xac - 0x8c];
    TArray<BYTE> Defaults;
};

struct FStateFrame : public FFrame {
    BYTE unk_14[4];
    UState *StateNode;
    BYTE unk_1c[0x28 - 0x1c];
    INT LatentAction;
};

#endif
