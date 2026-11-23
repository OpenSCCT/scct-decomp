// campaign_leaf_6edb50.cpp -- thiscall method at VA 0x10fedb50: replaces the block at 0x00 with
// a new one of Count slots of three ints (tag 0x12, allocator at VA 0x1131b3d8), fills the first
// array with 0xff, clears the count at 0x04 and stores the mask Count - 1 at 0x08. It then passes
// the second and third ints of every old slot whose first int is not -1 to the method at VA
// 0x10fed7e0 and frees the old block. The class, method and member names are invented; the
// offsets and addresses are the binary's.

#include "campaign_global_1131b3d8.h"

void Unk_10dffeb0(void* Dest, int Value, unsigned int Count);

class UnkType_10fedb50
{
public:
    void Unk_10fedb50(int Count);
    void Unk_10fed7e0(int First, int Second);

private:
    int* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10fedb50::Unk_10fedb50
void UnkType_10fedb50::Unk_10fedb50(int Count)
{
    int* Old;
    int OldCount;
    int i;

    Old = unk_0;
    OldCount = unk_8 + 1;
    unk_0 = (int*)GUnk_1131b3d8->VirtualSlot4(Count * 3 * sizeof(int), 0x12);
    Unk_10dffeb0(unk_0, 0xff, Count * sizeof(int));
    unk_4 = 0;
    unk_8 = Count - 1;
    for ( i = 0; i < OldCount; i++ )
    {
        if ( Old[i] != -1 )
        {
            Unk_10fed7e0(Old[OldCount + i], Old[OldCount * 2 + i]);
        }
    }
    GUnk_1131b3d8->VirtualSlot5(Old, OldCount * 3 * sizeof(int), 0x12);
}
