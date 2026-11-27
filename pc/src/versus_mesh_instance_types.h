// Versus mesh-instance interfaces reached by animation and vertex extraction.
#ifndef VERSUS_MESH_INSTANCE_TYPES_H
#define VERSUS_MESH_INSTANCE_TYPES_H

struct FVector;
class AActor;
class FLevelSceneNode;
class UMesh;

enum EGetFrameTask {
    GetFrame_Render = 0, GetFrame_Positions = 1, GetFrame_Bones = 2, GetFrame_RootMotion = 3
};

class UPrimitive : public UObject
{
public:
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();

    BYTE unk_28[0x50 - 0x28];
};

class UMeshInstance : public UPrimitive
{
public:
    virtual AActor *GetActor();
    virtual void VirtualSlot31();
    virtual UMesh *GetMesh();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual INT GetAnimCount();
    virtual void *GetAnimIndexed(INT Index);
    virtual void *GetAnimNamed(FName Name);
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();
    virtual void VirtualSlot44();
    virtual FLOAT AnimGetFrameCount(void *Anim);
    virtual FLOAT AnimGetRate(void *Anim);
    virtual INT AnimGetNotifyCount(void *Anim);
    virtual void VirtualSlot48();
    virtual void VirtualSlot49();
    virtual void VirtualSlot50();
    virtual void VirtualSlot51();
    virtual UBOOL StopAnimating();
    virtual void VirtualSlot53();
    virtual void VirtualSlot54();
    virtual void VirtualSlot55();
    virtual void VirtualSlot56();
    virtual void VirtualSlot57();
    virtual void VirtualSlot58();
    virtual FName GetActiveAnimSequence(INT Channel);
    virtual FLOAT GetActiveAnimRate(INT Channel);
    virtual FLOAT GetActiveAnimFrame(INT Channel);
    virtual void SetAnimFrame(INT Channel, FLOAT Frame, INT UnitFlag);
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
    virtual void GetMeshVerts(AActor *Owner, FVector *Out, INT Stride, INT &Count);
    BYTE unk_50[0x28];
};

#endif
