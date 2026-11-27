// Elements read by the Versus level's BSP and collision queries.
#ifndef VERSUS_LEVEL_COLLISION_H
#define VERSUS_LEVEL_COLLISION_H

#include "versus_engine_classes.h"

#include "versus_scene_model_types.h"

#include "versus_mem_stack.h"

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
    FMemStack::FTaggedMemory *SavedChunk;
};

#endif
