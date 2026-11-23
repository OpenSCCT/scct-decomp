// campaign_leaf_3c8420.cpp -- one function at file offset 0x3c8420, preferred VA 0x10cc8420. It
// empties an array of 0x9c-byte elements (data at 0x0, count at 0x4, capacity at 0x8): it destroys
// every element (destructor at 0x10cc8300), sets the capacity to Slack and the count to 0, and
// reallocates the data through virtual slot 1 of the allocator at 0x111c88a0 with the retail tag
// "FArray". The class, method, member and parameter names are invented; the offsets, the
// slot and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_1090ba70
{
public:
    ~UnkType_1090ba70();

    unsigned char unk_0[0xc];
};

class UnkType_1090d050
{
public:
    ~UnkType_1090d050()
    {
        Unk_1090d050(0, unk_4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_1090d050(int Index, int Count);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10cc8300
{
public:
    ~UnkType_10cc8300();

    unsigned char unk_0[0x34];
    UnkType_1090ba70 unk_34;
    unsigned char unk_40[0x18];
    UnkType_1090d050 unk_58;
    UnkType_1090ba70 unk_64;
    UnkType_1090ba70 unk_70;
    UnkType_1090ba70 unk_7c;
    UnkType_1090ba70 unk_88;
    unsigned char unk_94[0x8];
};

class UnkType_10cc8420
{
public:
    void Unk_10cc8420(int Slack);

    UnkType_10cc8300* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10cc8420::Unk_10cc8420
void UnkType_10cc8420::Unk_10cc8420(int Slack)
{
    int Index;

    for ( Index = 0; Index < unk_4; Index++ )
    {
        unk_0[Index].~UnkType_10cc8300();
    }
    unk_8 = Slack;
    unk_4 = 0;
    unk_0 = (UnkType_10cc8300*)GUnk_111c88a0->Realloc(unk_0, unk_8 * 0x9c, L"FArray");
}
