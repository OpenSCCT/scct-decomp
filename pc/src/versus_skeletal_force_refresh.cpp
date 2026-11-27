// Retail UObject mesh-instance virtual interface as used by ForceBoneRefresh.
#include "versus_build.h"
#include "unreal_object.h"

class AActor;
class FLevelSceneNode;

enum EGetFrameTask {
    GetFrame_Render = 0, GetFrame_Positions = 1, GetFrame_Bones = 2, GetFrame_RootMotion = 3
};

class UPrimitive : public UObject {
public:
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
};

class UMeshInstance : public UPrimitive {
public:
    virtual AActor *GetActor();
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
    virtual void VirtualSlot63();
    virtual void VirtualSlot64();
    virtual void VirtualSlot65();
    virtual void GetFrame(AActor *Owner, FLevelSceneNode *SceneNode, void *Vertices, INT Stride,
                          INT &VertexCount, EGetFrameTask Task);
    virtual void VirtualSlot67();
    virtual void VirtualSlot68();
    virtual void VirtualSlot69();
    virtual void VirtualSlot70();
};

class ULodMeshInstance : public UMeshInstance {
public:
    virtual void VirtualSlot71();
};

class USkeletalMeshInstance : public ULodMeshInstance {
public:
    virtual void VirtualSlot72();
    virtual void VirtualSlot73();
    virtual void ForceBoneRefresh();
};

void USkeletalMeshInstance::ForceBoneRefresh()
{
    AActor *owner = GetActor();
    if (owner) {
        INT unusedVertexCount;
        GetFrame(owner, 0, 0, 0, unusedVertexCount, GetFrame_Bones);
    }
}
