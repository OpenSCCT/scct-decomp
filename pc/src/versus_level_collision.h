// Elements read by the Versus level's BSP and collision queries.
#ifndef VERSUS_LEVEL_COLLISION_H
#define VERSUS_LEVEL_COLLISION_H

#include "versus_engine_classes.h"

struct FBspNode {
    BYTE unk_00[0x2c];
    INT iSurf;
    BYTE unk_30[0x5c - 0x30];
};

struct FBspSurf {
    BYTE unk_00[0x14];
    DWORD PolyFlags;
    BYTE unk_18[0x2c - 0x18];
};

// The collision query uses this prefix of the model.
class UModel : public UPrimitive {
public:
    BYTE unk_50[4];
    TTransArray<FBspNode> Nodes;
    BYTE unk_64[0x94 - 0x64];
    TTransArray<FBspSurf> Surfs;
};

struct FTaggedMemory;

class FMemStack {
public:
    BYTE *Top;
    BYTE *End;
    INT DefaultChunkSize;
    FTaggedMemory *TopChunk;

    void FreeChunks(FTaggedMemory *NewTopChunk);
};

extern FMemStack GMem;

class FMemMark {
public:
    FMemMark(FMemStack &InMem)
        : Mem(&InMem), Top(InMem.Top), SavedChunk(InMem.TopChunk) {}

    void Pop()
    {
        if (SavedChunk != Mem->TopChunk)
            Mem->FreeChunks(SavedChunk);
        Mem->Top = Top;
    }

private:
    FMemStack *Mem;
    BYTE *Top;
    FTaggedMemory *SavedChunk;
};

#endif
