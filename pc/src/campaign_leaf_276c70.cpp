// campaign_leaf_276c70.cpp -- method at VA 0x10b76c70: returns false unless the object reached
// through the method at VA 0x10a0e220 of the object at 0x04 of the record at 0x1c (given the
// record's byte at 0x0c) has, at 0x64, an object whose method at VA 0x10a45b50 returns nonzero, and
// the object at 0x30 is set with entries in its vector of 60-byte entries at 0x68 (count and
// indexes taken as shorts). It then looks back from the entry before the one at the short index
// 0xa8 for the first entry whose handler at 0x1c is set and is rejected by the method at VA
// 0x10b76380 for what the method at VA 0x10b76410 returns for the handler's first word; when one is
// found it sets bit 1 of the byte at 0xb4 of the object at 0x30; it passes one more than the found
// index, or 0 when none is found, then 0 and 0 to that object's method at VA 0x10d2a830. Returns
// whether an entry was found. The vector never allocates here, so the default allocator stands in.
// The class, member and method names are invented; the offsets and the addresses are the binary's.

#include <vector>

class UnkType_10b76c70_Handler
{
public:
    int unk_00;
};

class UnkType_10b76c70_Entry
{
public:
    unsigned char unk_00[0x1c];
    UnkType_10b76c70_Handler* unk_1c;
    unsigned char unk_20[0x3c - 0x20];
};

class UnkType_10b76c70_30
{
public:
    void Unk_10d2a830(int Index, int First, int Second);

    unsigned char unk_00[0x68];
    std::vector<UnkType_10b76c70_Entry> unk_68;
    unsigned char unk_78[0xa8 - 0x78];
    short unk_a8;
    unsigned char unk_aa[0xb4 - 0xaa];
    unsigned char unk_b4;
};

class UnkType_10b76c70_64
{
public:
    int Unk_10a45b50();
};

class UnkType_10b76c70_Found
{
public:
    unsigned char unk_00[0x64];
    UnkType_10b76c70_64* unk_64;
};

class UnkType_10b76c70_Source
{
public:
    UnkType_10b76c70_Found* Unk_10a0e220(unsigned char Index);
};

class UnkType_10b76c70_Record
{
public:
    unsigned char unk_00[0x04];
    UnkType_10b76c70_Source* unk_04;
    unsigned char unk_08[0x0c - 0x08];
    unsigned char unk_0c;
};

class UnkType_10b76c70
{
public:
    bool Unk_10b76c70();
    int Unk_10b76410(int Value);
    bool Unk_10b76380(int Value);

private:
    unsigned char unk_00[0x1c];
    UnkType_10b76c70_Record* unk_1c;
    unsigned char unk_20[0x30 - 0x20];
    UnkType_10b76c70_30* unk_30;
};

// UnkType_10b76c70::Unk_10b76c70
bool UnkType_10b76c70::Unk_10b76c70()
{
    if ( !unk_1c->unk_04->Unk_10a0e220(unk_1c->unk_0c)->unk_64->Unk_10a45b50() )
    {
        return false;
    }
    if ( !unk_30 || !(short)unk_30->unk_68.size() )
    {
        return false;
    }
    int Found = -1;
    for ( int Index = unk_30->unk_a8 - 1; Index >= 0 && Found == -1; Index-- )
    {
        UnkType_10b76c70_Handler* Handler = unk_30->unk_68[(short)Index].unk_1c;
        if ( Handler && !Unk_10b76380(Unk_10b76410(Handler->unk_00)) )
        {
            Found = Index;
        }
    }
    if ( Found == -1 )
    {
        unk_30->Unk_10d2a830(0, 0, 0);
    }
    else
    {
        unk_30->unk_b4 |= 2;
        unk_30->Unk_10d2a830(Found + 1, 0, 0);
    }
    return Found != -1;
}
