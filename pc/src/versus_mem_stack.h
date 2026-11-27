#ifndef VERSUS_MEM_STACK_H
#define VERSUS_MEM_STACK_H

#include "versus_build.h"
#include "unreal_types.h"

class FMemStack
{
public:
    struct FTaggedMemory
    {
        FTaggedMemory *Next;
        INT DataSize;
        BYTE Data[1];
    };

    BYTE *Top;
    BYTE *End;
    INT DefaultChunkSize;
    FTaggedMemory *TopChunk;

    static FTaggedMemory *UnusedChunks;

    ~FMemStack() { Exit(); }
    void Tick() {}
    void Exit();
    BYTE *AllocateNewChunk(INT MinSize);
    void FreeChunks(FTaggedMemory *NewTopChunk);

    BYTE *PushBytes(INT AllocSize, INT Align)
    {
        BYTE *Result = (BYTE *)(((INT)Top + (Align - 1)) & ~(Align - 1));
        Top = Result + AllocSize;
        if (Top > End)
        {
            AllocateNewChunk(AllocSize + Align);
            Result = (BYTE *)(((INT)Top + (Align - 1)) & ~(Align - 1));
            Top = Result + AllocSize;
        }
        return Result;
    }
};

extern FMemStack GSceneMem;
extern FLOAT NEAR_CLIPPING_PLANE;

inline void *operator new(unsigned int Size, FMemStack &Mem)
{
    return Mem.PushBytes(Size, 8);
}

#endif
