// campaign_leaf_4b47e0.cpp -- one function at file offset 0x4b47e0, preferred VA 0x10db47e0.
// The constructor runs the base constructor at 0x10d9d560 and clears the int at offset 0 and the
// short at offset 4. The class and member names are invented; the offset and the bytes are the
// binary's.

class UnkType_10db47e0_Base
{
public:
    UnkType_10db47e0_Base();
};

class UnkType_10db47e0 : public UnkType_10db47e0_Base
{
public:
    int unk_0;
    short unk_4;

    UnkType_10db47e0();
};

// UnkType_10db47e0::UnkType_10db47e0
UnkType_10db47e0::UnkType_10db47e0()
{
    unk_0 = 0;
    unk_4 = 0;
}
