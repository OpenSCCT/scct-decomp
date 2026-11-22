// campaign_leaf_2f8b50.cpp -- a member function at VA 0x10bf8b50 that returns, by value, the
// 12-byte result of the member at VA 0x10bf8a30 of the object the pointer at 0x420 refers to. The
// class, method and member names are invented; the offsets and addresses are the binary's.

struct UnkType_10bf8a30_Result
{
    float unk_00;
    float unk_04;
    float unk_08;
};

class UnkType_10bf8a30
{
public:
    UnkType_10bf8a30_Result Unk_10bf8a30();
};

class UnkType_10bf8b50
{
public:
    UnkType_10bf8a30_Result Unk_10bf8b50();

private:
    unsigned char unk_000[0x420];
    UnkType_10bf8a30* unk_420;
};

// UnkType_10bf8b50::Unk_10bf8b50
UnkType_10bf8a30_Result UnkType_10bf8b50::Unk_10bf8b50()
{
    return unk_420->Unk_10bf8a30();
}
