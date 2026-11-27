// Skeletal mesh animation linkups, active-channel lookups and sequence counts.
#include "versus_build.h"
#include "versus_mesh_animation_channels.h"

typedef void *HMeshAnim;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;
extern const TCHAR FArray_Tag[]; // 0x10c10974, TEXT("FArray")

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    INT __stdcall AddZeroed(INT ElementSize, INT n); // RVA 0x15400
    void Shrink(INT ElementSize)
    {
        if (ArrayMax != ArrayNum)
        {
            ArrayMax = ArrayNum;
            Data = GMalloc->Realloc(Data, ArrayMax * ElementSize, FArray_Tag);
        }
    }
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
    void Shrink(); // RVA 0xc0d50 for TArray<MeshAnimChannel>
};

// 0x2c bytes.
struct FMeshAnimSeq
{
    FName Name;
    TArray<FName> Groups;
    INT StartFrame;
    INT NumFrames;
    FLOAT Rate;
    TArray<INT> Notifys;
    INT Pad28;
};

class UMeshAnimation
{
public:
    char Pad0[0x44];
    TArray<FMeshAnimSeq> AnimSeqs; // 0x44
};

class UMeshAnimation;
class UMesh;
class USkeletalMesh
{
public:
    char Pad0[0x1dc];
    UMeshAnimation *DefaultAnim; // 0x1dc
    UMesh *DefaultRefMesh;        // 0x1e0
};

// 0x18 bytes.
struct MeshAnimLinkup
{
    UMeshAnimation *Anim;
    UMesh *RefMesh;
    BYTE unk_08[4];
    TArray<INT> BoneLinks;
};

extern const FLOAT GZeroFloat;       // 0x10c109f8, 0.0f
extern const FLOAT DefaultAnimRate;  // 0x10c10e20, 30.0f

#define DUMMY(n) virtual void Slot##n();

class USkeletalMeshInstance
{
public:
    DUMMY(0) DUMMY(1) DUMMY(2) DUMMY(3) DUMMY(4) DUMMY(5) DUMMY(6) DUMMY(7)
    DUMMY(8) DUMMY(9) DUMMY(10) DUMMY(11) DUMMY(12) DUMMY(13) DUMMY(14) DUMMY(15)
    DUMMY(16) DUMMY(17) DUMMY(18) DUMMY(19) DUMMY(20) DUMMY(21) DUMMY(22) DUMMY(23)
    DUMMY(24) DUMMY(25) DUMMY(26) DUMMY(27) DUMMY(28) DUMMY(29) DUMMY(30) DUMMY(31)
    virtual USkeletalMesh *GetMesh();                    // slot 32 (0x80)
    DUMMY(33) DUMMY(34) DUMMY(35) DUMMY(36) DUMMY(37) DUMMY(38)
    virtual INT GetAnimCount();                          // slot 39 (0x9c)
    virtual HMeshAnim GetAnimIndexed(INT InIndex);       // slot 40 (0xa0)
    virtual HMeshAnim GetAnimNamed(FName InName);        // slot 41 (0xa4)
    DUMMY(42) DUMMY(43) DUMMY(44) DUMMY(45)
    virtual FLOAT AnimGetRate(HMeshAnim InAnim);         // slot 46 (0xb8)
    DUMMY(47) DUMMY(48) DUMMY(49) DUMMY(50) DUMMY(51) DUMMY(52) DUMMY(53) DUMMY(54)
    DUMMY(55) DUMMY(56) DUMMY(57) DUMMY(58) DUMMY(59) DUMMY(60) DUMMY(61) DUMMY(62)
    DUMMY(63) DUMMY(64) DUMMY(65) DUMMY(66) DUMMY(67) DUMMY(68) DUMMY(69) DUMMY(70)
    DUMMY(71)
    virtual void LinkupsChanged();                       // slot 72 (0x120)
    DUMMY(73) DUMMY(74)
    virtual UMeshAnimation *CurrentSkelAnim(INT Slot);   // slot 75 (0x12c)

    char Pad4[0xa4];
    TArray<MeshAnimLinkup> AnimLinkups;   // 0xa8
    char PadB4[0x4c];
    TArray<MeshAnimChannel> Channels;     // 0x100

    USkeletalMeshInstance() {}

    UBOOL SetAnimLinkup(UMeshAnimation *Anim, UMesh *RefMesh);
    void ActualizeAnimLinkups();
    UBOOL ValidateAnimChannel(INT Channel);
    FName GetActiveAnimSequence(INT Channel)
    {
        FName Result;
        Result.Index = (Channel >= 0 && Channel < Channels.Num()) ? Channels(Channel).AnimSequence.Index : 0;
        return Result;
    }
    FLOAT GetActiveAnimRate(INT Channel);
};

// Out-of-line helpers in retail.
#pragma auto_inline(off)
// RVA 0xc0d50 (another function; defined for its ESI convention).
template <class T> void TArray<T>::Shrink()
{
    FArray::Shrink(sizeof(T));
}

#include "versus_skeletal_animation_linkups.inl"

// RVA 0xb5910 (another function; defined so the link gives it its EBX/EDI convention).
UBOOL USkeletalMeshInstance::ValidateAnimChannel(INT Channel)
{
    if (Channel > 256 || Channel < 0)
        return 0;
    if (Channels.Num() <= Channel)
    {
        do
            Channels.AddZeroed(sizeof(MeshAnimChannel), 1);
        while (Channels.Num() <= Channel);
        Channels.Shrink();
    }
    return 1;
}


// RVA 0xb6f00
INT USkeletalMeshInstance::GetAnimCount()
{
    ActualizeAnimLinkups();
    INT Count = 0;
    for (INT i = 0; i < AnimLinkups.Num(); i++)
        if (AnimLinkups(i).Anim)
            Count += AnimLinkups(i).Anim->AnimSeqs.Num();
    return Count;
}

// RVA 0xb6f40
FLOAT USkeletalMeshInstance::GetActiveAnimRate(INT Channel)
{
    if (ValidateAnimChannel(Channel))
    {
        FLOAT Rate = AnimGetRate(GetAnimNamed(GetActiveAnimSequence(Channel)));
        if (Rate != GZeroFloat)
            return Rate;
    }
    return DefaultAnimRate;
}

// RVA 0xb6fa0
HMeshAnim USkeletalMeshInstance::GetAnimIndexed(INT InIndex)
{
    if (CurrentSkelAnim(0) && CurrentSkelAnim(0)->AnimSeqs.Num() > InIndex)
        return &CurrentSkelAnim(0)->AnimSeqs(InIndex);
    return 0;
}

// RVA 0xb7000
HMeshAnim USkeletalMeshInstance::GetAnimNamed(FName InName)
{
    ActualizeAnimLinkups();
    for (INT i = 0; i < AnimLinkups.Num(); i++)
    {
        UMeshAnimation *Anim = AnimLinkups(i).Anim;
        if (Anim)
            for (INT a = 0; a < Anim->AnimSeqs.Num(); a++)
                if (InName == Anim->AnimSeqs(a).Name)
                    return &AnimLinkups(i).Anim->AnimSeqs(a);
    }
    return 0;
}

#pragma auto_inline(on)

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);
FLOAT Driver_b6f40(void *Mem, INT Channel, INT Other)
{
    USkeletalMeshInstance *M = new (Mem) USkeletalMeshInstance;
    Escape(M);
    M->ValidateAnimChannel(Other);
    return M->GetActiveAnimRate(Channel);
}
