// campaign_leaf_49e1b0.cpp -- thiscall method at VA 0x10d9e1b0. It returns whether the value at
// the current pointer of its stream at 0x0 (the inline at 0x10d9d6a0) equals the stream's
// position (0x10dcddb0) less 4. The class and method names are invented.

#include "campaign_global_1131b150.h"

void Unk_10d98090(const void* Source, void* Dest);

class UnkType_10d9e1b0_Stream
{
public:
    int* Unk_10dcdda0();
    int Unk_10dcddb0();
};

class UnkType_10d9e1b0
{
public:
    bool Unk_10d9e1b0();

    int Unk_10d9d6a0()
    {
        if ( GUnk_1131b150 )
        {
            int Value;

            Unk_10d98090(unk_0->Unk_10dcdda0(), &Value);
            return Value;
        }
        return *unk_0->Unk_10dcdda0();
    }

private:
    UnkType_10d9e1b0_Stream* unk_0;
};

// UnkType_10d9e1b0::Unk_10d9e1b0
bool UnkType_10d9e1b0::Unk_10d9e1b0()
{
    return Unk_10d9d6a0() == unk_0->Unk_10dcddb0() - 4;
}
