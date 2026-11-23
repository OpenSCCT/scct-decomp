// campaign_leaf_4dd5d0.cpp -- one function at file offset 0x4dd5d0, preferred VA 0x10ddd5d0.
// The constructor runs the base constructor at 0x10d8b2d0 and builds the member at offset 4, whose
// inline constructor stores the result of its method at 0x10ddd000 at its offset 4 and clears its
// offset 8. The class, method and member names are invented; the offset and the bytes are the
// binary's.

class UnkType_10ddd5d0_Base
{
public:
    int unk_0;

    UnkType_10ddd5d0_Base();
};

class UnkType_10ddd000
{
public:
    int unk_0;
    int unk_4;
    int unk_8;

    UnkType_10ddd000()
    {
        unk_4 = Unk_10ddd000();
        unk_8 = 0;
    }

    int Unk_10ddd000();
};

class UnkType_10ddd5d0 : public UnkType_10ddd5d0_Base
{
public:
    UnkType_10ddd000 unk_4;

    UnkType_10ddd5d0();
};

// UnkType_10ddd5d0::UnkType_10ddd5d0
UnkType_10ddd5d0::UnkType_10ddd5d0()
{
}
