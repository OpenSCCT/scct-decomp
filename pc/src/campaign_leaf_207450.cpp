// campaign_leaf_207450.cpp -- thiscall method at VA 0x10b07450. When the word at 0x20 is zero it
// returns false. Otherwise it stores the words at 0x20, 0x24 and 0x70 through its first three
// arguments, copies the string at 0x2c into the buffer its fourth argument points to, passes the
// member at 0x1c4 to the method at VA 0x1095c6d0 of its fifth argument and returns true. The
// class, method and member names are invented.

#include <string.h>

class UnkType_10b07450_Target
{
public:
    void Unk_1095c6d0(void* Value);
};

class UnkType_10b07450
{
public:
    bool Unk_10b07450(int* First, int* Second, int* Third, char** Name,
                      UnkType_10b07450_Target* Target);

private:
    char unk_00[0x20];
    int unk_20;
    int unk_24;
    char unk_28[4];
    char unk_2c[0x44];
    int unk_70;
    char unk_74[0x150];
    char unk_1c4[4];
};

// UnkType_10b07450::Unk_10b07450
bool UnkType_10b07450::Unk_10b07450(int* First, int* Second, int* Third, char** Name,
                                    UnkType_10b07450_Target* Target)
{
    if ( !unk_20 )
    {
        return false;
    }
    *First = unk_20;
    *Second = unk_24;
    *Third = unk_70;
    strcpy(*Name, unk_2c);
    Target->Unk_1095c6d0(unk_1c4);
    return true;
}
