// campaign_leaf_5053a0.cpp -- one function at file offset 0x5053a0, preferred VA 0x10e053a0.
// The constructor runs the base constructor at 0x10fedaf0 and then builds the member at offset
// 0xc with the constructor at 0x10e016a0. The class and member names are invented; the offset and
// the bytes are the binary's.

class UnkType_10fedaf0
{
public:
    int unk_0;
    int unk_4;
    int unk_8;

    UnkType_10fedaf0();
};

class UnkType_10e016a0
{
public:
    int unk_0;

    UnkType_10e016a0();
};

class UnkType_10e053a0 : public UnkType_10fedaf0
{
public:
    UnkType_10e016a0 unk_c;

    UnkType_10e053a0();
};

// UnkType_10e053a0::UnkType_10e053a0
UnkType_10e053a0::UnkType_10e053a0()
{
}
