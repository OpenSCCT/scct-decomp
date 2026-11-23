// campaign_leaf_208150.cpp -- thiscall method at VA 0x10b08150. It finds the entry of the list at
// 0x15b4 whose first word equals its first argument, copies the entry's 128-character strings at
// 0x5c and 0xdd into the buffers its other two arguments point to and returns true; it returns
// false when no entry matches. The class, method and member names are invented; the list is the
// compiler's library.

#include <list>
#include <string.h>

struct UnkType_10b08150_Entry
{
    int unk_00;
    char unk_04[0x58];
    char unk_5c[0x81];
    char unk_dd[0x83];
};

class UnkType_10b08150
{
public:
    bool Unk_10b08150(int Id, char* First, char* Second);

private:
    char unk_0000[0x15b4];
    std::list<UnkType_10b08150_Entry> unk_15b4;
};

// UnkType_10b08150::Unk_10b08150
bool UnkType_10b08150::Unk_10b08150(int Id, char* First, char* Second)
{
    std::list<UnkType_10b08150_Entry>::iterator It;

    for ( It = unk_15b4.begin(); It != unk_15b4.end(); ++It )
    {
        if ( Id == It->unk_00 )
        {
            strncpy(First, It->unk_5c, 0x80);
            strncpy(Second, It->unk_dd, 0x80);
            return true;
        }
    }
    return false;
}
