// campaign_leaf_20f070.cpp -- thiscall method at VA 0x10b0f070. When the object at 0x68 is set, it
// empties that object's array at 0x8f8 (its data reallocated to nothing through slot 1 of the
// allocator at VA 0x111c88a0). It then looks for the 0x64-byte entry of the array at 0x40 whose
// word at 0x1c equals the given key; when one is found it keeps a pointer to it at 0x4c and the key
// at 0x38. The class, method and member names are invented.

#include "campaign_global_111c88a0.h"

class UnkType_10b0f070_Array
{
public:
    // UnkType_10b0f070_Array::Empty
    void Empty(int Slack = 0)
    {
        unk_4 = 0;
        unk_8 = Slack;
        unk_0 = GUnk_111c88a0->Realloc(unk_0, unk_8 * 4, L"FArray");
    }

private:
    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10b0f070_Owner
{
public:
    char unk_000[0x8f8];
    UnkType_10b0f070_Array unk_8f8;
};

struct UnkType_10b0f070_Entry
{
    char unk_00[0x1c];
    int unk_1c;
    char unk_20[0x64 - 0x20];
};

class UnkType_10b0f070
{
public:
    void Unk_10b0f070(int Key);

private:
    char unk_00[0x38];
    int unk_38;
    int unk_3c;
    UnkType_10b0f070_Entry* unk_40;
    int unk_44;
    int unk_48;
    UnkType_10b0f070_Entry* unk_4c;
    char unk_50[0x68 - 0x50];
    UnkType_10b0f070_Owner* unk_68;
};

// UnkType_10b0f070::Unk_10b0f070
void UnkType_10b0f070::Unk_10b0f070(int Key)
{
    if ( unk_68 )
    {
        unk_68->unk_8f8.Empty();
    }
    for ( int i = 0; i < unk_44; i++ )
    {
        if ( unk_40[i].unk_1c == Key )
        {
            unk_4c = &unk_40[i];
            unk_38 = Key;
            return;
        }
    }
}
