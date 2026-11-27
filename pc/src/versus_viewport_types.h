#ifndef VERSUS_VIEWPORT_TYPES_H
#define VERSUS_VIEWPORT_TYPES_H

class FExec {
public:
    virtual UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar) = 0;
};

class APlayerController;
class UCanvas;

// Engine registers Player with a size of 0x68 and Viewport with a size of 0x190.
class UPlayer : public UObject, public FOutputDevice, public FExec {
public:
    APlayerController *Actor;
    BYTE unk_34[0x68 - 0x34];
};

class UViewport : public UPlayer {
public:
    UCanvas *Canvas;
    BYTE unk_6c[0xa0 - 0x6c];
    INT SizeX, SizeY;
    BYTE unk_a8[0x190 - 0xa8];
};

#endif
