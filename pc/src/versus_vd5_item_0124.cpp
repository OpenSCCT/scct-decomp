/* Versus RVA 0xb71f0 and 0xb7260: USkeletalMeshInstance vtable slots 73 and 63.
   0xb71f0 has the shape of UE2 USkeletalMeshInstance::FindAnimObjectForSequence:
   it actualizes the animation linkups and returns the first linked
   UMeshAnimation that has the named sequence.
   0xb7260 sets a channel sequence and frame and fires the notifies passed
   between the previous and the new frame (name SetAnimFrameNotify assumed).
   The non-virtual helpers 0xb6d80 / 0xb5910 are link-time-optimised callees;
   their bodies here follow retail closely so the linker picks the same
   register conventions. Virtual slot names are assumed from UE2. */
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

class FName {
public:
    INT Index;
};

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);          /* retail 0x10915400 */
    INT Num() const { return ArrayNum; }
};

class AActor;
class USkeletalMeshInstance;

class UNotifyObject {                             /* UAnimNotify */
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21();
    virtual void Notify(USkeletalMeshInstance *Instance, AActor *Owner);  /* +0x58 */
};

typedef void *HMeshAnim;

class UMeshAnimation {
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21();
    virtual HMeshAnim GetAnimNamed(FName Name);   /* +0x58 */
};

struct MeshAnimLinkup {                           /* 0x18 bytes */
    UMeshAnimation *Anim;
    DWORD Pad[5];
};

struct MeshAnimChannel {                          /* 0x90 bytes */
    DWORD Pad0;
    INT MeshAnimIndex;                            /* 0x04 */
    FName AnimSequence;                           /* 0x08 */
    DWORD Pad0c;
    FLOAT AnimFrame;                              /* 0x10 */
    DWORD Pad[0x1f];
};

struct UMesh {
    unsigned char Pad[0x1dc];
    UMeshAnimation *DefaultAnim;                  /* 0x1dc */
    DWORD DefaultRefs;                            /* 0x1e0 */
};

typedef unsigned short TCHAR;
class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
};
extern FMalloc *GMalloc;
extern const TCHAR ChannelArrayTag[];             /* retail 0x10c10974 */

/* TArray<MeshAnimChannel> */
class FChannelArray : public FArray {
public:
    __declspec(noinline) void Shrink();           /* retail 0x109c0d50 */
};

void FChannelArray::Shrink()
{
    if (ArrayMax != ArrayNum) {
        ArrayMax = ArrayNum;
        Data = GMalloc->Realloc(Data, ArrayMax * sizeof(MeshAnimChannel), ChannelArrayTag);
    }
}

class USkeletalMeshInstance {
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29();
    virtual AActor *GetActor();                                   /* 30, +0x78 */
    virtual void V31();
    virtual UMesh *GetMesh();                                     /* 32, +0x80 */
    virtual void V33(); virtual void V34(); virtual void V35();
    virtual void V36(); virtual void V37(); virtual void V38(); virtual void V39();
    virtual void V40(); virtual void V41(); virtual void V42(); virtual void V43();
    virtual void V44(); virtual void V45(); virtual void V46();
    virtual INT AnimGetNotifyCount(HMeshAnim Anim);               /* 47, +0xbc */
    virtual FLOAT AnimGetNotifyTime(HMeshAnim Anim, INT Index);   /* 48, +0xc0 */
    virtual void V49();
    virtual UNotifyObject *AnimGetNotifyObject(HMeshAnim Anim, INT Index); /* 50, +0xc8 */
    virtual void V51(); virtual void V52(); virtual void V53(); virtual void V54();
    virtual void V55(); virtual void V56(); virtual void V57(); virtual void V58();
    virtual void V59(); virtual void V60(); virtual void V61(); virtual void V62();
    virtual UBOOL SetAnimFrameNotify(FName Sequence, FLOAT Frame, FLOAT Delta, INT Channel); /* 63, +0xfc */
    virtual void V64(); virtual void V65(); virtual void V66(); virtual void V67();
    virtual void V68(); virtual void V69(); virtual void V70(); virtual void V71();
    virtual void LinkupsChanged();                /* 72, +0x120, name assumed */
    virtual UMeshAnimation *FindAnimObjectForSequence(FName Sequence); /* 73, +0x124 */

    __declspec(noinline) UBOOL AddAnimLinkup(UMeshAnimation *Anim, DWORD Refs); /* retail 0x109b6d10 */
    __declspec(noinline) UBOOL ValidateAnimChannel(INT Channel); /* retail 0x109b5910 */
    __declspec(noinline) void ActualizeAnimLinkups();           /* retail 0x109b6d80 */
    INT FindLinkup(UMeshAnimation *Anim)
    {
        for (INT i = 0; i < AnimLinkups.Num(); i++)
            if (((MeshAnimLinkup *)AnimLinkups.Data)[i].Anim == Anim)
                return i;
        return -1;
    }

    unsigned char Pad04[0xa4];
    FArray AnimLinkups;                           /* 0xa8 */
    unsigned char Pad0b4[0x4c];
    FChannelArray Blends;                                /* 0x100 */
};

UBOOL USkeletalMeshInstance::AddAnimLinkup(UMeshAnimation *Anim, DWORD Refs)
{
    if (Anim) {
        INT Found = -1;
        for (INT i = 0; i < AnimLinkups.Num(); i++) {
            if (((MeshAnimLinkup *)AnimLinkups.Data)[i].Anim == Anim) {
                Found = i;
                break;
            }
        }
        if (Found == -1) {
            INT Index = AnimLinkups.Add(1, sizeof(MeshAnimLinkup));
            ((MeshAnimLinkup *)AnimLinkups.Data)[Index].Anim = Anim;
            ((MeshAnimLinkup *)AnimLinkups.Data)[Index].Pad[0] = Refs;
        }
        LinkupsChanged();
    }
    return 1;
}

/* retail 0x109b6d80 */
void USkeletalMeshInstance::ActualizeAnimLinkups()
{
    if (this && AnimLinkups.Num() == 0 && GetMesh() && GetMesh()->DefaultAnim)
        AddAnimLinkup(GetMesh()->DefaultAnim, GetMesh()->DefaultRefs);
}

UBOOL USkeletalMeshInstance::ValidateAnimChannel(INT Channel)
{
    if (Channel > 256 || Channel < 0)
        return 0;
    if (Blends.Num() <= Channel) {
        do {
            Blends.Add(1, sizeof(MeshAnimChannel));
        } while (Blends.Num() <= Channel);
        Blends.Shrink();
    }
    return 1;
}

UMeshAnimation *USkeletalMeshInstance::FindAnimObjectForSequence(FName Sequence)
{
    ActualizeAnimLinkups();
    for (INT i = 0; i < AnimLinkups.Num(); i++) {
        UMeshAnimation *Anim = ((MeshAnimLinkup *)AnimLinkups.Data)[i].Anim;
        if (Anim && Anim->GetAnimNamed(Sequence))
            return ((MeshAnimLinkup *)AnimLinkups.Data)[i].Anim;
    }
    return 0;
}

UBOOL USkeletalMeshInstance::SetAnimFrameNotify(FName Sequence, FLOAT Frame, FLOAT Delta, INT Channel)
{
    if (!ValidateAnimChannel(Channel) || Blends.Num() <= Channel || Channel < 0)
        return 0;
    UMeshAnimation *MeshAnim = FindAnimObjectForSequence(Sequence);
    if (!MeshAnim)
        return 0;
    HMeshAnim Anim = MeshAnim->GetAnimNamed(Sequence);
    if (Anim) {
        for (INT i = 0; i < AnimGetNotifyCount(Anim); i++) {
            FLOAT PrevFrame = Frame - Delta;
            FLOAT Time = AnimGetNotifyTime(Anim, i);
            if ((Delta > 0.f && ((Time <= Frame && Time > PrevFrame) || PrevFrame + 1.f < Time))
                || (Delta < 0.f && Time >= Frame && Time < PrevFrame)) {
                UNotifyObject *Notify = AnimGetNotifyObject(Anim, i);
                if (Notify)
                    Notify->Notify(this, GetActor());
            }
        }
    }
    INT Index = FindLinkup(MeshAnim);
    ((MeshAnimChannel *)Blends.Data)[Channel].MeshAnimIndex = Index;
    ((MeshAnimChannel *)Blends.Data)[Channel].AnimFrame = Frame;
    ((MeshAnimChannel *)Blends.Data)[Channel].AnimSequence = Sequence;
    return 1;
}

// Scaffolding for the link, not part of the unit: retail reaches both
// functions only through the vtable, so the driver builds an object whose
// vtable references them.
void Escape(void *);
void Driver_b71f0()
{
    USkeletalMeshInstance Obj;
    Escape(&Obj);
}
