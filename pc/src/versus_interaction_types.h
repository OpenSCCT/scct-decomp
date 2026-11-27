#ifndef VERSUS_INTERACTION_TYPES_H
#define VERSUS_INTERACTION_TYPES_H

class UCanvas;
class UViewport;
class UInteractionMaster;

class UInteractions : public UObject {
public:
    virtual ~UInteractions();
};

class UInteraction : public UInteractions {
public:
    virtual ~UInteraction();
    virtual void VirtualSlot22();
    virtual UBOOL NativeKeyType(BYTE &iKey, TCHAR Unicode);
    virtual UBOOL NativeKeyEvent(BYTE &iKey, BYTE &State, FLOAT Delta);
    virtual void NativeTick(FLOAT DeltaTime);
    virtual void NativePreRender(UCanvas *Canvas);
    virtual void NativePostRender(UCanvas *Canvas);

    DWORD bActive : 1;
    DWORD bVisible : 1;
    DWORD bRequiresTick : 1;
    DWORD bNativeEvents : 1;
    UViewport *ViewportOwner;
    UInteractionMaster *Master;
};

#endif
