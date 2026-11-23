// campaign_leaf_71d1b0.cpp -- one function at file offset 0x71d1b0, preferred VA 0x1101d1b0. It
// constructs an object in place at its argument when that is not null: the base constructor at
// VA 0x10e68230 runs and the words from 0x2c down to 0x20 and from 0x3c down to 0x30 are zeroed.
// The class and function names are invented; the offsets and the callee's address are the
// binary's.

inline void* operator new(unsigned int Size, void* Place)
{
    return Place;
}

class UnkType_1101d1b0_Base
{
public:
    UnkType_1101d1b0_Base();

    unsigned char unk_0[0x20];
};

class UnkType_1101d1b0 : public UnkType_1101d1b0_Base
{
public:
    UnkType_1101d1b0()
    {
        unk_2c = 0;
        unk_28 = 0;
        unk_24 = 0;
        unk_20 = 0;
        unk_3c = 0;
        unk_38 = 0;
        unk_34 = 0;
        unk_30 = 0;
    }

    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3c;
};

// Unk_1101d1b0
void Unk_1101d1b0(void* Place)
{
    new (Place) UnkType_1101d1b0;
}
