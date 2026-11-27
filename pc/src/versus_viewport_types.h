#ifndef VERSUS_VIEWPORT_TYPES_H
#define VERSUS_VIEWPORT_TYPES_H

class FExec {
public:
    virtual UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar) = 0;
};

class APlayerController;
class UCanvas;
class UInteraction;
class FRenderInterface;

class AActor;
class URenderDevice;
class FRenderTarget {
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual INT GetWidth();
    virtual INT GetHeight();
};

// This array clears 16-byte elements and reserves four entries after the viewport pass.
class UnnamedPlaneArray_68dc0 : public FArray {
public:
    void Reset();
};


// Engine registers Player with a size of 0x68 and Viewport with a size of 0x190.
class UPlayer : public UObject, public FOutputDevice, public FExec {
public:
    APlayerController *Actor;
    BYTE unk_34[0x58 - 0x34];
    TArray<UInteraction *> LocalInteractions;
    BYTE unk_64[4];
};

class UViewport : public UPlayer {
public:
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void Present();
    UCanvas *Canvas;
    BYTE unk_6c[4];
    URenderDevice *RenDev;
    BYTE unk_74[0x80 - 0x74];
    UnnamedPlaneArray_68dc0 RenderEntries;
    BYTE unk_8c[0xa0 - 0x8c];
    INT SizeX, SizeY;
    BYTE unk_a8[0xe4 - 0xa8];
    FRenderTarget RenderTarget;
    BYTE unk_e8[0x140 - 0xe8];
    FRenderInterface *RI;
    BYTE unk_144[8];
    UBOOL Precaching;
    UBOOL PendingPresent;
    UBOOL bHitTesting;
    BYTE unk_158[0x18c - 0x158];
    AActor *FirstPersonActor;

    void DrawPendingView();
    void UpdateScreenEffects();
};

#endif
