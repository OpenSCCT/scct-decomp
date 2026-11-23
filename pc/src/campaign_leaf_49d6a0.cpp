// campaign_leaf_49d6a0.cpp -- thiscall method at VA 0x10d9d6a0. It returns the 4-byte value at
// the current pointer (0x10dcdda0) of its stream at 0x0, converted through 0x10d98090 while the
// flag at 0x1131b150 is set. The class and method names are invented.

#include "campaign_global_1131b150.h"

void Unk_10d98090(const void* Source, void* Dest);

class UnkType_10d9d6a0_Stream
{
public:
    int* Unk_10dcdda0();
};

class UnkType_10d9d6a0
{
public:
    int Unk_10d9d6a0();

private:
    UnkType_10d9d6a0_Stream* unk_0;
};

// UnkType_10d9d6a0::Unk_10d9d6a0
int UnkType_10d9d6a0::Unk_10d9d6a0()
{
    if ( GUnk_1131b150 )
    {
        int Value;

        Unk_10d98090(unk_0->Unk_10dcdda0(), &Value);
        return Value;
    }
    return *unk_0->Unk_10dcdda0();
}
