// Work item 0381: RVA 0x11aa20 and 0x11aa80.
// Neutral names: no symbol evidence beyond the published remove_array helper.

typedef int INT;
typedef unsigned long DWORD;

struct UnnamedActor_11aa20
{
    char Pad0[0x2e8];
    DWORD Flags2E8; // bit 0x8000 marks the entry for removal (likely bDeleteMe)
};

struct FArray
{
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

// Published as remove_array (src/versus_arrays.c): FArray::Remove(Index, Count, ElementSize).
// Its integer arguments are one-word structs, so __fastcall passes them on the stack.
struct SizeArg { INT Value; SizeArg(INT V) : Value(V) {} };
void __fastcall remove_array(FArray *Array, SizeArg Index, SizeArg Count, SizeArg ElementSize);

// Compacts a pointer array from Start onward, dropping null and deleted entries.
// Returns 1 when something was removed.
INT __fastcall CompactActorList_11aa20(FArray *List, INT Out)
{
    for (INT i = Out; i < List->ArrayNum; i++) {
        UnnamedActor_11aa20 *A = ((UnnamedActor_11aa20 **)List->Data)[i];
        if (A && !(A->Flags2E8 & 0x8000)) {
            if (Out != i)
                ((UnnamedActor_11aa20 **)List->Data)[Out] = A;
            Out++;
        }
    }
    if (Out != List->ArrayNum) {
        remove_array(List, Out, List->ArrayNum - Out, 4);
        return 1;
    }
    return 0;
}

struct FListPad { FArray A; INT Pad; };

struct UnnamedOwner_11aa80
{
    char Pad0[0x2c];
    FArray MainList;          // 0x2c
    char Pad38[0x5c - 0x38];
    FListPad Lists[9];        // 0x5c .. 0xec, stride 0x10
    char PadEC[0x138 - 0xec];
    DWORD DirtyFlags;         // 0x138
    char Pad13C[0x3a5c - 0x13c];
    INT MainListStart;        // 0x3a5c

    void CleanLists();
};

void UnnamedOwner_11aa80::CleanLists()
{
    if (DirtyFlags) {
        CompactActorList_11aa20(&MainList, MainListStart);
        if (DirtyFlags & 0x8)   CompactActorList_11aa20(&Lists[0].A, 0);
        if (DirtyFlags & 0x10)  CompactActorList_11aa20(&Lists[1].A, 0);
        if (DirtyFlags & 0x20)  CompactActorList_11aa20(&Lists[2].A, 0);
        if (DirtyFlags & 0x40)  CompactActorList_11aa20(&Lists[3].A, 0);
        if (DirtyFlags & 0x80)  CompactActorList_11aa20(&Lists[4].A, 0);
        if (DirtyFlags & 0x100) CompactActorList_11aa20(&Lists[5].A, 0);
        if (DirtyFlags & 0x200) CompactActorList_11aa20(&Lists[6].A, 0);
        if (DirtyFlags & 0x400) CompactActorList_11aa20(&Lists[7].A, 0);
        if (DirtyFlags & 0x800) CompactActorList_11aa20(&Lists[8].A, 0);
        DirtyFlags = 0;
    }
}

// Scaffolding for the LTCG link, not part of the unit.
void Driver_11aa80(UnnamedOwner_11aa80 *O) { O->CleanLists(); }
