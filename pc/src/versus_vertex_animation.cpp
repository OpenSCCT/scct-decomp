// Named sequence lookups on legacy vertex mesh instances.
#include "versus_build.h"
#include "unreal_object.h"
#include "versus_animation_sequence.h"

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
    BYTE unk_28[0x50-0x28];
};
class UMesh : public UPrimitive {
public:
    virtual void VirtualSlot30();
    class UMeshInstance *DefaultInstance;  // +0x50
};
class ULodMesh : public UMesh {
public:
    BYTE unk_54[0xf4-0x54];
};
class UVertMesh : public ULodMesh {
public:
    BYTE unk_f4[0x118-0xf4];
    TArray<FMeshAnimSeq> AnimSeqs;
};

class UMeshInstance : public UPrimitive {
public:
    virtual class AActor *GetActor();
    virtual void VirtualSlot31();
    virtual UMesh *GetMesh();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual INT GetAnimCount();
    virtual FMeshAnimSeq *GetAnimIndexed(INT Index);
    virtual FMeshAnimSeq *GetAnimNamed(FName Name);
};
class ULodMeshInstance : public UMeshInstance {
public:
    BYTE unk_50[0x78 - 0x50];
};
class UVertMeshInstance : public ULodMeshInstance {
public:
    virtual FMeshAnimSeq *GetAnimNamed(FName Name);
    FMeshAnimSeq *FindAnimSeq(FName Name);
    UVertMesh *GetVertMesh() { return (UVertMesh *)GetMesh(); }
};

FMeshAnimSeq *UVertMeshInstance::GetAnimNamed(FName Name)
{
    for (INT i = 0; i < GetVertMesh()->AnimSeqs.Num(); ++i)
        if (Name == GetVertMesh()->AnimSeqs(i).Name)
            return &GetVertMesh()->AnimSeqs(i);
    return 0;
}

FMeshAnimSeq *UVertMeshInstance::FindAnimSeq(FName Name)
{
    UVertMesh *mesh = GetVertMesh();
    for (INT i = 0; i < mesh->AnimSeqs.Num(); ++i)
        if (Name == mesh->AnimSeqs(i).Name)
            return &mesh->AnimSeqs(i);
    return 0;
}
