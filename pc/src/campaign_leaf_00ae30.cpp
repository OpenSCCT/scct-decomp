// campaign_leaf_00ae30.cpp -- destructor at VA 0x1090ae30 of a class whose vtable is at VA
// 0x110b7e08: closes the handle at 0x3c with CloseHandle when it is set and clears it, then runs
// the inline destructor of the base class whose vtable is at VA 0x110b7e68. The class and member
// names are invented; the offset and the addresses are the binary's.

#include "campaign_import_CloseHandle.h"

class UnkType_110b7e68
{
public:
    virtual ~UnkType_110b7e68()
    {
    }

private:
    unsigned char unk_04[0x38];
};

class UnkType_1090ae30 : public UnkType_110b7e68
{
public:
    virtual ~UnkType_1090ae30();

private:
    HANDLE unk_3c;
};

// UnkType_1090ae30::~UnkType_1090ae30
UnkType_1090ae30::~UnkType_1090ae30()
{
    if ( unk_3c )
    {
        CloseHandle(unk_3c);
        unk_3c = 0;
    }
}
