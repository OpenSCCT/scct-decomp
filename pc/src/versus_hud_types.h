#ifndef VERSUS_HUD_TYPES_H
#define VERSUS_HUD_TYPES_H

// The Engine.HUD registration records a 0x49c-byte actor.
class AHUD : public AActor {
public:
    void eventPostRender(class UCanvas *Canvas);
    BYTE Unknown2f8[0x3e0 - 0x2f8];
    APlayerController *PlayerOwner;
    BYTE Unknown3e4[0x49c - 0x3e4];
};

#endif
