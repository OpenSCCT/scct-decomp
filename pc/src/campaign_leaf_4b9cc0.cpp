// campaign_leaf_4b9cc0.cpp -- one function at file offset 0x4b9cc0, preferred VA 0x10db9cc0.
// The constructor builds the members at offsets 0 and 0x10, whose inline constructors store the
// results of their methods at 0x10db94d0 and 0x10db95b0 at their offset 4 and clear their offset
// 8. The class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10db94d0
{
public:
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;

    UnkType_10db94d0()
    {
        unk_4 = Unk_10db94d0();
        unk_8 = 0;
    }

    int Unk_10db94d0();
};

class UnkType_10db95b0
{
public:
    int unk_0;
    int unk_4;
    int unk_8;

    UnkType_10db95b0()
    {
        unk_4 = Unk_10db95b0();
        unk_8 = 0;
    }

    int Unk_10db95b0();
};

class UnkType_10db9cc0
{
public:
    UnkType_10db94d0 unk_0;
    UnkType_10db95b0 unk_10;

    UnkType_10db9cc0();
};

// UnkType_10db9cc0::UnkType_10db9cc0
UnkType_10db9cc0::UnkType_10db9cc0()
{
}
