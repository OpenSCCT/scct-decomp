#ifndef VERSUS_VIEWPORT_TYPES_H
#define VERSUS_VIEWPORT_TYPES_H

#include "versus_base_texture.h"

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
class UViewport;

// The viewport owns its render target. Its cache ID and owner are set by UViewport's constructor.
#pragma pack(push, 4)
class FViewportRenderTarget : public FRenderTarget {
public:
    virtual unsigned __int64 GetCacheId();
    virtual INT GetRevision();
    virtual INT GetWidth();
    virtual INT GetHeight();
    virtual INT GetFirstMip();
    virtual INT GetNumMips();
    virtual ETextureFormat GetFormat();
    virtual BYTE GetUClamp();
    virtual BYTE GetVClamp();

    UViewport *Viewport;
    unsigned __int64 CacheId;
};
#pragma pack(pop)

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
    BYTE unk_a8[0xb8 - 0xa8];
    INT ColorBytes;
    BYTE unk_bc[0xe4 - 0xbc];
    FViewportRenderTarget RenderTarget;
    BYTE unk_f4[0x130 - 0xf4];
    DOUBLE CurrentTime;
    BYTE unk_138[0x140 - 0x138];
    FRenderInterface *RI;
    BYTE unk_144[4];
    BYTE NextStencilBit;
    BYTE unk_149[3];
    UBOOL Precaching;
    UBOOL PendingPresent;
    UBOOL bHitTesting;
    BYTE unk_158[0x18c - 0x158];
    AActor *FirstPersonActor;

    void DrawPendingView();
    void UpdateScreenEffects();
};

#endif
