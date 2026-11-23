// campaign_leaf_278530.cpp -- method at VA 0x10b78530: when the object at 0x24 is set, deletes the
// member at 0x1c of every 60-byte entry of that object's vector at 0x68 that has one (its two
// strings at 0x0c and 0x00 destroyed through the destructor at VA 0x1090ba70, its memory freed
// through slot 2 of the allocator at VA 0x111c88a0), with the count and the index taken as shorts,
// then calls the object's method at VA 0x10d2f530. The vector never allocates here, so the default
// allocator stands in. The class, member and method names are invented; the offsets and the
// addresses are the binary's.

#include <vector>

#include "campaign_global_111c88a0.h"

// operator delete
inline void operator delete(void* Original)
{
    GUnk_111c88a0->Free(Original);
}

class UnkType_10b78530_String
{
public:
    ~UnkType_10b78530_String();

private:
    unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b78530_Data
{
public:
    UnkType_10b78530_String unk_00;
    UnkType_10b78530_String unk_0c;
};

class UnkType_10b78530_Entry
{
public:
    unsigned char unk_00[0x1c];
    UnkType_10b78530_Data* unk_1c;
    unsigned char unk_20[0x3c - 0x20];
};

class UnkType_10b78530_24
{
public:
    void Unk_10d2f530();

    unsigned char unk_00[0x68];
    std::vector<UnkType_10b78530_Entry> unk_68;
};

class UnkType_10b78530
{
public:
    void Unk_10b78530();

private:
    unsigned char unk_00[0x24];
    UnkType_10b78530_24* unk_24;
};

// UnkType_10b78530::Unk_10b78530
void UnkType_10b78530::Unk_10b78530()
{
    if ( unk_24 )
    {
        for ( int Index = 0; Index < (short)unk_24->unk_68.size(); Index++ )
        {
            UnkType_10b78530_Data* Data = unk_24->unk_68[(short)Index].unk_1c;
            if ( Data )
            {
                delete Data;
            }
        }
        unk_24->Unk_10d2f530();
    }
}
