// campaign_leaf_49e6e0.cpp -- thiscall method at VA 0x10d9e6e0. It writes the given count of
// 8-byte values to its stream at 0x0 (0x10dce120 with -1): one at a time through 0x10d98190
// while the flag at 0x1131b150 is set, else all at once. Unless its flag at 0x14 is set, it then
// stores the stream's position (0x10dcddb0) less 4 at the stream's current pointer (0x10dcdda0),
// converted through 0x10d98170 while the flag is set. The value type is a guess. The class,
// method and parameter names are invented.

#include "campaign_global_1131b150.h"

void Unk_10d98170(const void* Source, void* Dest);
void Unk_10d98190(const void* Source, void* Dest);

class UnkType_10d9e6e0_Stream
{
public:
    int* Unk_10dcdda0();
    int Unk_10dcddb0();
    void Unk_10dce120(const void* Data, int Size, int Flags);
};

class UnkType_10d9e6e0
{
public:
    void Unk_10d9e6e0(const __int64* Data, unsigned int Count);

private:
    UnkType_10d9e6e0_Stream* unk_0;
    unsigned char unk_4[0x10];
    bool unk_14;
};

// UnkType_10d9e6e0::Unk_10d9e6e0
void UnkType_10d9e6e0::Unk_10d9e6e0(const __int64* Data, unsigned int Count)
{
    const __int64* Item = Data;

    if ( GUnk_1131b150 )
    {
        unsigned int Index;

        for ( Index = 0; Index < Count; Index++ )
        {
            __int64 Converted;

            Unk_10d98190(Item, &Converted);
            unk_0->Unk_10dce120(&Converted, 8, -1);
            Item++;
        }
    }
    else
    {
        unk_0->Unk_10dce120(Item, Count * sizeof(__int64), -1);
    }
    if ( !unk_14 )
    {
        if ( GUnk_1131b150 )
        {
            int Position = unk_0->Unk_10dcddb0() - 4;

            Unk_10d98170(&Position, unk_0->Unk_10dcdda0());
        }
        else
        {
            *unk_0->Unk_10dcdda0() = unk_0->Unk_10dcddb0() - 4;
        }
    }
}
