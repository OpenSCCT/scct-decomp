// campaign_leaf_49e8e0.cpp -- thiscall method at VA 0x10d9e8e0. It writes the given 4-byte value
// to its stream at 0x0 (0x10dce120 with size 4 and -1), passed through 0x10d98170 first while
// the flag at 0x1131b150 is set. Unless its flag at 0x14 is set, it then stores the stream's
// position (0x10dcddb0) less 4 at the stream's current pointer (0x10dcdda0), converted the same
// way. It returns this object. The value's type is a guess; the methods at 0x10d9e850 and
// 0x10d9e970 compile to the same bytes. The class, method and parameter names are invented.

#include "campaign_global_1131b150.h"

void Unk_10d98170(const void* Source, void* Dest);

class UnkType_10d9e8e0_Stream
{
public:
    int* Unk_10dcdda0();
    int Unk_10dcddb0();
    void Unk_10dce120(const void* Data, int Size, int Flags);
};

class UnkType_10d9e8e0
{
public:
    UnkType_10d9e8e0& Unk_10d9e8e0(unsigned int Value);

private:
    UnkType_10d9e8e0_Stream* unk_0;
    unsigned char unk_4[0x10];
    bool unk_14;
};

// UnkType_10d9e8e0::Unk_10d9e8e0
UnkType_10d9e8e0& UnkType_10d9e8e0::Unk_10d9e8e0(unsigned int Value)
{
    if ( GUnk_1131b150 )
    {
        unsigned int Converted;

        Unk_10d98170(&Value, &Converted);
        unk_0->Unk_10dce120(&Converted, 4, -1);
    }
    else
    {
        unk_0->Unk_10dce120(&Value, 4, -1);
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
    return *this;
}
