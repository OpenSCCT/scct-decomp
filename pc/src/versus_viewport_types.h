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
    BYTE unk_6c[0xa0 - 0x6c];
    INT SizeX, SizeY;
    BYTE unk_a8[0x140 - 0xa8];
    FRenderInterface *RI;
    BYTE unk_144[0x190 - 0x144];
};

#endif
