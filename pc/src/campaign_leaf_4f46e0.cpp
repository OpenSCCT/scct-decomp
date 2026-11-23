// campaign_leaf_4f46e0.cpp -- one function at file offset 0x4f46e0, preferred VA 0x10df46e0.
// The constructor runs the base constructor at 0x10d9d560 and copies the short at offset 0x48 of
// the object the cdecl function at 0x10df2d30 returns into the short at offset 0. The class,
// function and member names are invented; the offset and the bytes are the binary's.

class UnkType_10df46e0_Base
{
public:
    UnkType_10df46e0_Base();
};

struct UnkType_10df46e0_Result
{
    unsigned char unk_0[0x48];
    short unk_48;
};

UnkType_10df46e0_Result* Unk_10df2d30();

class UnkType_10df46e0 : public UnkType_10df46e0_Base
{
public:
    short unk_0;

    UnkType_10df46e0();
};

// UnkType_10df46e0::UnkType_10df46e0
UnkType_10df46e0::UnkType_10df46e0()
{
    unk_0 = Unk_10df2d30()->unk_48;
}
