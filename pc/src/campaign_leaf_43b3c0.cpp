// campaign_leaf_43b3c0.cpp -- thiscall at VA 0x10d3b3c0: calls the method at VA 0x10a0f390 of the
// member at offset 0x14 with its argument, 0 and -1, and returns the result. All names are
// invented.

class UnkType_10a0f390
{
public:
    int Unk_10a0f390(int Value, int Start, int Count);
};

class UnkType_10d3b3c0
{
public:
    int Unk_10d3b3c0(int Value);

private:
    unsigned char unk_00[0x14];
    UnkType_10a0f390 unk_14;
};

// UnkType_10d3b3c0::Unk_10d3b3c0
int UnkType_10d3b3c0::Unk_10d3b3c0(int Value)
{
    return unk_14.Unk_10a0f390(Value, 0, -1);
}
