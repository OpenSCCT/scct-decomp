// campaign_leaf_4b48d0.cpp -- one function at file offset 0x4b48d0, preferred VA 0x10db48d0.
// The constructor runs the base constructor at 0x10d9d560 and clears the int at offset 0, the
// short at offset 4 and the int at offset 0x104. The class and member names are invented; the
// offset and the bytes are the binary's.

class UnkType_10db48d0_Base
{
public:
    UnkType_10db48d0_Base();
};

class UnkType_10db48d0 : public UnkType_10db48d0_Base
{
public:
    int unk_0;
    short unk_4;
    unsigned char unk_6[0xfe];
    int unk_104;

    UnkType_10db48d0();
};

// UnkType_10db48d0::UnkType_10db48d0
UnkType_10db48d0::UnkType_10db48d0()
{
    unk_0 = 0;
    unk_4 = 0;
    unk_104 = 0;
}
