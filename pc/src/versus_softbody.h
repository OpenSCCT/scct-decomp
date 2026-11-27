#ifndef VERSUS_SOFTBODY_H
#define VERSUS_SOFTBODY_H

struct FDynamicActor;
struct FDynamicLightList;
class FLevelSceneNode;
class FProjectorRenderInfo;
class FRenderInterface;
template<class T> struct TList;

// Engine.ESoftBody: 0x15c bytes, 58 virtual functions
class UESoftBody : public UPrimitive {
public:
    virtual ~UESoftBody();
    virtual void Render(FDynamicActor *DynamicActor, FLevelSceneNode *SceneNode, FDynamicLightList *Lights,
                        TList<FProjectorRenderInfo *> *Projectors, FRenderInterface *RI);
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

    BYTE unk_50[4];
    AActor *Owner;
    BYTE unk_58[0x128 - 0x58];
    FLOAT LastRenderTime;
    BYTE unk_12c[0x15c - 0x12c];
};

#endif
