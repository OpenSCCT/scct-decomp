// Stop the skeletal animation channels and optionally clear bone controllers and extra blends.
#include "versus_build.h"
#include "unreal_script.h"
#include "versus_skeletal_animation_instance.h"

class UField : public UObject
{
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
    BYTE unk_68[0x88 - 0x68];
};
class UClass : public UState {
public:
    BYTE unk_88[0x114 - 0x88];
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = (UClass *)TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return SomeBase == 0;
}

template <class T>
inline T *Cast(UObject *Src)
{
    return Src && Src->IsA(T::StaticClass()) ? (T *)Src : 0;
}

class AActor : public UObject
{
public:
    BYTE unk_28[0x1bc - 0x28];
    UMesh *Mesh;                   // +0x1bc
    BYTE unk_1c0[0x14];
    UMeshInstance *MeshInstance;   // +0x1d4

    void execStopAnimating(FFrame &Stack, RESULT_DECL);
};

// USkeletalMeshInstance::StopAnimating (RVA 0xb59d0, callee for LTCG convention)
UBOOL USkeletalMeshInstance::StopAnimating(UBOOL ClearAllButBase)
{
    for (INT i = 0; i < Channels.Num(); i++) {
        Channels(i).AnimRate = 0.0f;
        Channels(i).TweenRate = 0.0f;
    }
    if (ClearAllButBase) {
        BoneAdjustments.Empty();
        BoneDirections.Empty();
        for (INT i = 1; i < Channels.Num(); i++) {
            Channels(i).CurrentAlpha = 0.0f;
            Channels(i).AnimSequence = NAME_None;
        }
    }
    return 1;
}

// AActor::execStopAnimating (RVA 0x123a70)
void AActor::execStopAnimating(FFrame &Stack, RESULT_DECL)
{
    P_GET_UBOOL_OPTX(ClearAllButBase, 0);
    P_FINISH;
    if (Mesh) {
        Mesh->MeshGetInstance(this);
        USkeletalMeshInstance *SkelInst = Cast<USkeletalMeshInstance>(MeshInstance);
        if (SkelInst)
            SkelInst->StopAnimating(ClearAllButBase);
        else
            MeshInstance->StopAnimating();
    }
}
