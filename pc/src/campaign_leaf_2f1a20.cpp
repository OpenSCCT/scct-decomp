// campaign_leaf_2f1a20.cpp -- a member function at VA 0x10bf1a20 that appends its argument to the
// array at 0x408: the array's member at VA 0x10bf1920, given 4 and 1, returns the new index, and
// the argument is stored in the array's data at that index. The class, method and member names are
// invented; the offsets and addresses are the binary's.

class UnkType_10bf1920
{
public:
    int Unk_10bf1920(int First, int Second);

    int* unk_00;
};

class UnkType_10bf1a20
{
public:
    void Unk_10bf1a20(int Value);

private:
    unsigned char unk_000[0x408];
    UnkType_10bf1920 unk_408;
};

// UnkType_10bf1a20::Unk_10bf1a20
void UnkType_10bf1a20::Unk_10bf1a20(int Value)
{
    int Index = unk_408.Unk_10bf1920(4, 1);
    unk_408.unk_00[Index] = Value;
}
