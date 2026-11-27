#ifndef VERSUS_SBASE_INTERACTION_TYPES_H
#define VERSUS_SBASE_INTERACTION_TYPES_H

class UClass;
struct FFrame;

struct FMoverLockInfo {
    class AMover *MoverToLock;
    BYTE ActionBeforeLock;
};

// SBase.SInteractObject: 0x364 bytes, 80 virtual functions
class ASInteractObject : public AActor {
public:
    virtual ~ASInteractObject();
    virtual UBOOL VirtualSlot78(void *Argument);
    virtual void VirtualSlot79();

    BYTE    unk_2f8[8];
    INT     Priority;
    FString unk_304;
    BYTE    unk_310[0x1c];
    BYTE    unk_32c[0x2c];
    DWORD   unk_358;
    BYTE    unk_35c[0x8];

    void execDoTouch(FFrame &Stack, void *const Result);
    void execTriggerEventServer(FFrame &Stack, void *const Result);
    void execUnTriggerEventServer(FFrame &Stack, void *const Result);
    void execSetPriority(FFrame &Stack, void *const Result);
};

// SBase.STriggerInteraction: 0x380 bytes, 80 virtual functions
class ASTriggerInteraction : public ASInteractObject {
public:
    virtual ~ASTriggerInteraction();

    static UClass PrivateStaticClass;
    class ASPlayerController *InstigatorTempo;
    BITFIELD bIsActive : 1, bHackable : 1, bMaintain : 1;
    class ASInterrupteur *OwnerInterrupteur;
    FLOAT MinTriggerTime, LocalRemainingTimeSeconds, Alpha;
    INT RemainingTime;
};

// SBase.SAlarm: 0x360 bytes, 78 virtual functions
class ASAlarm : public AActor {
public:
    virtual ~ASAlarm();

#ifdef VERSUS_LTCG_H
    // The legacy destructor receipts model the private calling convention of the two owning arrays.
    TArray<UnkType_4>     Events;
    TArrayLtcg<UnkType_4> ObjectiveTriggersToLock;
    TArrayLtcg<UnkType_8> MoversToLock;
#else
    TArray<FName> Events;
    TArray<class ASObjectiveTrigger *> ObjectiveTriggersToLock;
    TArray<FMoverLockInfo> MoversToLock;
#endif
    FString               AlarmName;
    FString               AlarmDescription;
    FString               AlarmDescriptionSpy;
    class ASBasicGamePlayObject *TriggerActor;
    INT StartTime, LastCurrentTime;
    FLOAT LastAlphaTime;
    INT Duration, i;
    BYTE MessagePriority;
    BITFIELD bAlarmOn : 1, bLocalAlarmOn : 1;
};

#endif
