// Work item 0321: Versus RVA 0x8e8e0-0x8ee47.
// Replication helpers of UE2 actors: GetOptimizedRepList overrides (the DOREP
// pattern, whose function-local static property pointer is what gives these
// functions their exception frame), a clamp of two floats on ALight, and
// AActor::ReplicateAnim.

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

template<class T> inline T Clamp(const T X, const T Min, const T Max)
{
    return X < Min ? Min : X < Max ? X : Max;
}

// Name index as FindPropertyChecked (0x17720) takes it.
struct FName
{
    INT Index;
    FName() {}
    FName(INT InIndex) : Index(InIndex) {}
};
inline UBOOL operator!=(const FName &A, const FName &B) { return A.Index != B.Index; }

// Name argument of the property lookup wrapper at 0x92280. Retail builds these
// arguments in place with a tracked temporary, which needs a copy constructor.
// Neutral name.
struct FRepName
{
    INT Index;
    FRepName(INT InIndex) : Index(InIndex) {}
    FRepName(const FRepName &Other) : Index(Other.Index) {}
};

class UObject {};
class UClass;
struct FPropertyRetirement;

class UPackageMap : public UObject
{
public:
    virtual void Slot0(); virtual void Slot1(); virtual void Slot2(); virtual void Slot3();
    virtual void Slot4(); virtual void Slot5(); virtual void Slot6(); virtual void Slot7();
    virtual void Slot8(); virtual void Slot9(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21();
    virtual UBOOL CanSerializeObject(UObject *Obj);
};

class UActorChannel : public UObject
{
public:
    BYTE Pad0[0x7e];
    BYTE bActorMustStayDirty;
};

class UProperty : public UObject
{
public:
    BYTE Pad0[0x56];
    _WORD RepIndex;
};

// 0x10917720: finds a property by name in an outer class, failing if missing.
UProperty *FindPropertyChecked(UClass *Class, UClass *Outer, FName A, FName B, FName Name, INT Flags);
extern UClass UProperty_PrivateStaticClass;   // 0x10cc8610
extern UClass Class_10cc52a8;                 // outer of property 0x7f6 (neutral name)
extern UClass AZoneInfo_PrivateStaticClass;   // 0x10cc5938
extern UClass Class_10cc76c0;                 // outer of property 0xdf0 (neutral name)

// 0x10992280: FindPropertyChecked for UProperty, kept out of line in retail.
__declspec(noinline) UProperty *FindRepProperty(UClass *Outer, FRepName A, FRepName B, FRepName Name, INT Flags)
{
    return FindPropertyChecked(&UProperty_PrivateStaticClass, Outer, FName(A.Index), FName(B.Index), FName(Name.Index), Flags);
}

inline UBOOL NEQ(UObject *A, UObject *B, UPackageMap *Map, UActorChannel *Channel)
{
    if (Map->CanSerializeObject(A))
        return A != B;
    Channel->bActorMustStayDirty = 1;
    return B != 0;
}

struct FAnimRep
{
    FName AnimSequence;
    BYTE  bAnimLoop;
    BYTE  AnimRate;
    BYTE  AnimFrame;
    BYTE  TweenRate;
};

class AActor : public UObject
{
public:
    BYTE     Pad0[0x2a8 - 4];
    FAnimRep SimAnim;                         // 0x2a8
    BYTE     Pad1[0x2de - 0x2b0];
    BYTE     Role;                            // 0x2de
    BYTE     Pad2[0x2e8 - 0x2df];
    DWORD    Bits2e8_0 : 12;
    DWORD    bReplicatedFlag : 1;             // 0x2e8 bit 12, property 0x7f6 (neutral name)
    DWORD    Bits2e8_13 : 19;
    DWORD    Bits2ec_0 : 2;                   // 0x2ec
    DWORD    bNetDirty : 1;
    DWORD    Bits2ec_3 : 7;
    DWORD    bReplicateAnimations : 1;
    DWORD    Pad2f0;

    virtual INT *GetOptimizedRepList(BYTE *Recent, FPropertyRetirement *Retire, INT *Ptr, UPackageMap *Map, UActorChannel *Channel);
    void ReplicateAnim(INT Channel, FName SequenceName, FLOAT Rate, FLOAT Frame, FLOAT TweenRate, FLOAT Last, UBOOL bLooping);
};

// RVA 0x8e8e0. Class not identified (neutral name). LTCG object.
class UnnamedActor_8e8e0 : public AActor
{
public:
    DWORD bRepCondition : 1;                  // 0x2f4 bit 0
    BYTE  Pad3[0x330 - 0x2f8];
    INT   RepValue;                           // 0x330, property 0xdf0

    virtual INT *GetOptimizedRepList(BYTE *Recent, FPropertyRetirement *Retire, INT *Ptr, UPackageMap *Map, UActorChannel *Channel);
};

INT *UnnamedActor_8e8e0::GetOptimizedRepList(BYTE *Recent, FPropertyRetirement *Retire, INT *Ptr, UPackageMap *Map, UActorChannel *Channel)
{
    Ptr = AActor::GetOptimizedRepList(Recent, Retire, Ptr, Map, Channel);
    if (bRepCondition && bNetDirty && Role == 4)
    {
        if (RepValue != ((UnnamedActor_8e8e0 *)Recent)->RepValue)
        {
            static UProperty *spRepValue = FindRepProperty(&Class_10cc76c0, FRepName(0), FRepName(0), FRepName(0xdf0), 0);
            *Ptr++ = spRepValue->RepIndex;
        }
    }
    return Ptr;
}

// RVA 0x8e9c0: ALight vtable slot 77. Clamps two values into [Min, Max].
class ALight : public AActor
{
public:
    DWORD Pad3;
    FLOAT RangeMin;                           // 0x2f8
    FLOAT RangeMax;                           // 0x2fc

    void ClampToRange(FLOAT &A, FLOAT &B);
};

void ALight::ClampToRange(FLOAT &A, FLOAT &B)
{
    A = Clamp(A, RangeMin, RangeMax);
    B = Clamp(B, RangeMin, RangeMax);
}

// RVA 0x8ea50.
class ASBulletImpact : public AActor
{
public:
    virtual INT *GetOptimizedRepList(BYTE *Recent, FPropertyRetirement *Retire, INT *Ptr, UPackageMap *Map, UActorChannel *Channel);
};

INT *ASBulletImpact::GetOptimizedRepList(BYTE *Recent, FPropertyRetirement *Retire, INT *Ptr, UPackageMap *Map, UActorChannel *Channel)
{
    Ptr = AActor::GetOptimizedRepList(Recent, Retire, Ptr, Map, Channel);
    if (Role == 4)
    {
        if (bReplicatedFlag != ((AActor *)Recent)->bReplicatedFlag)
        {
            static UProperty *spReplicatedFlag = FindPropertyChecked(&UProperty_PrivateStaticClass, &Class_10cc52a8, FName(0), FName(0), FName(0x7f6), 0);
            *Ptr++ = spReplicatedFlag->RepIndex;
        }
    }
    return Ptr;
}

// RVA 0x8eb10.
class ASImpactEffectBase : public AActor
{
public:
    virtual INT *GetOptimizedRepList(BYTE *Recent, FPropertyRetirement *Retire, INT *Ptr, UPackageMap *Map, UActorChannel *Channel);
};

INT *ASImpactEffectBase::GetOptimizedRepList(BYTE *Recent, FPropertyRetirement *Retire, INT *Ptr, UPackageMap *Map, UActorChannel *Channel)
{
    Ptr = AActor::GetOptimizedRepList(Recent, Retire, Ptr, Map, Channel);
    if (Role == 4)
    {
        if (bReplicatedFlag != ((AActor *)Recent)->bReplicatedFlag)
        {
            static UProperty *spReplicatedFlag = FindPropertyChecked(&UProperty_PrivateStaticClass, &Class_10cc52a8, FName(0), FName(0), FName(0x7f6), 0);
            *Ptr++ = spReplicatedFlag->RepIndex;
        }
    }
    return Ptr;
}

// RVA 0x8ebd0.
class AZoneInfo : public AActor
{
public:
    DWORD    Pad3;
    UObject *ZoneObject;                      // 0x2f8, property 0xbc2 (neutral name)

    virtual INT *GetOptimizedRepList(BYTE *Recent, FPropertyRetirement *Retire, INT *Ptr, UPackageMap *Map, UActorChannel *Channel);
};

INT *AZoneInfo::GetOptimizedRepList(BYTE *Recent, FPropertyRetirement *Retire, INT *Ptr, UPackageMap *Map, UActorChannel *Channel)
{
    Ptr = AActor::GetOptimizedRepList(Recent, Retire, Ptr, Map, Channel);
    if (bNetDirty && Role == 4)
    {
        if (NEQ(ZoneObject, ((AZoneInfo *)Recent)->ZoneObject, Map, Channel))
        {
            static UProperty *spZoneObject = FindPropertyChecked(&UProperty_PrivateStaticClass, &AZoneInfo_PrivateStaticClass, FName(0), FName(0), FName(0xbc2), 0);
            *Ptr++ = spZoneObject->RepIndex;
        }
    }
    return Ptr;
}

// RVA 0x8ecc0 (LTCG: this in ESI, Channel in EAX, bLooping in EBX).
void AActor::ReplicateAnim(INT Channel, FName SequenceName, FLOAT Rate, FLOAT Frame, FLOAT TweenRate, FLOAT Last, UBOOL bLooping)
{
    if (bReplicateAnimations && Channel == 0)
    {
        FLOAT NewRate = (Last == 0.f) ? 124.f : (Clamp(Rate, -4.f, 4.f) + 4.f) * 31.f;
        if (SimAnim.AnimSequence != SequenceName || (FLOAT)SimAnim.AnimRate != NewRate || SimAnim.bAnimLoop != bLooping)
            bNetDirty = 1;
        SimAnim.AnimSequence = SequenceName;
        SimAnim.bAnimLoop    = (SimAnim.bAnimLoop & ~1) | bLooping;
        SimAnim.AnimRate     = (BYTE)NewRate;
        SimAnim.AnimFrame    = (BYTE)((Clamp(Frame, -1.f, 1.f) + 1.f) * 127.f);
        SimAnim.TweenRate    = (BYTE)(Clamp(TweenRate, 0.f, 63.f) * 4.f);
    }
}

// ---------------------------------------------------------------------------
// Scaffolding for the LTCG links, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }

INT *Driver_8e8e0(AActor *A, BYTE *Recent, FPropertyRetirement *Retire, INT *Ptr, UPackageMap *Map, UActorChannel *Channel)
{
    new(A) UnnamedActor_8e8e0;
    return A->GetOptimizedRepList(Recent, Retire, Ptr, Map, Channel);
}

// Mirrors the retail caller at 0x10982170 (an animation channel object).
struct FAnimChannelCaller
{
    BYTE    Pad0[0x54];
    AActor *Actor;
    BYTE    Pad1[0xb0 - 0x58];
    FName   Sequence;
    FLOAT   Rate;
    FLOAT   Frame;
    FLOAT   Last;
    FLOAT   Tween;
    BYTE    Pad2[0xd8 - 0xc4];
    UBOOL   bLoop;
};

void Driver_8ecc0(FAnimChannelCaller *C)
{
    C->Actor->ReplicateAnim(0, C->Sequence, C->Rate, C->Frame, C->Tween, C->Last, C->bLoop);
}
