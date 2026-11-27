// FMemStack (Core/UnMem.cpp), Unreal Engine 2.
#include "versus_mem_stack.h"

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;
extern const TCHAR MemChunk_Tag[]; // L"MemChunk"

inline void *appMalloc(INT Size, const TCHAR *Tag) { return GMalloc->Malloc(Size, Tag); }
inline void appFree(void *Ptr) { GMalloc->Free(Ptr); }
template <class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

void FMemStack::Exit()
{
    Tick();
    while (UnusedChunks)
    {
        void *Old = UnusedChunks;
        UnusedChunks = UnusedChunks->Next;
        appFree(Old);
    }
    UnusedChunks = 0;
}

BYTE *FMemStack::AllocateNewChunk(INT MinSize)
{
    FTaggedMemory *Chunk = 0;
    for (FTaggedMemory **Link = &UnusedChunks; *Link; Link = &(*Link)->Next)
    {
        // Find existing chunk.
        if ((*Link)->DataSize >= MinSize)
        {
            Chunk = *Link;
            *Link = (*Link)->Next;
            break;
        }
    }
    if (!Chunk)
    {
        // Create new chunk.
        INT DataSize = Max(MinSize, DefaultChunkSize - (INT)sizeof(FTaggedMemory));
        Chunk = (FTaggedMemory *)appMalloc(DataSize + sizeof(FTaggedMemory), MemChunk_Tag);
        Chunk->DataSize = DataSize;
    }
    Chunk->Next = TopChunk;
    TopChunk = Chunk;
    Top = Chunk->Data;
    End = Top + Chunk->DataSize;
    return Top;
}

void FMemStack::FreeChunks(FTaggedMemory *NewTopChunk)
{
    while (TopChunk != NewTopChunk)
    {
        FTaggedMemory *RemoveChunk = TopChunk;
        TopChunk = TopChunk->Next;
        RemoveChunk->Next = UnusedChunks;
        UnusedChunks = RemoveChunk;
    }
    if (TopChunk)
    {
        Top = TopChunk->Data;
        End = Top + TopChunk->DataSize;
    }
    else
    {
        Top = 0;
        End = 0;
    }
}

FMemStack GSceneMem = { 0, 0, 32768, 0 };
FLOAT NEAR_CLIPPING_PLANE = 2.f;

// Scaffolding for the link, not part of the unit.
void Escape(void *);
BYTE *Driver_577c0(FMemStack *S, INT N) { Escape(&GMalloc); Escape(&FMemStack::UnusedChunks); return S->AllocateNewChunk(N); }
#pragma inline_depth(0)
void Driver_57830(FMemStack *S, FMemStack::FTaggedMemory *M) { Escape(&FMemStack::UnusedChunks); S->FreeChunks(M); }
