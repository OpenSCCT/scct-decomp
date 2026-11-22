// campaign_leaf_318ec0.cpp -- one function at file offset 0x318ec0, preferred VA 0x10c18ec0. It
// exchanges two entries, chosen by its two index arguments, of the pointer-sized array whose data
// pointer is at offset 0x9ac. The class, method and member names are invented; the offset and the
// bytes are the binary's.

class UnkType_10c18ec0
{
public:
    unsigned char unk_0[0x9ac];
    int* unk_9ac;

    void SwapUnk9ac(int First, int Second);
};

// UnkType_10c18ec0::SwapUnk9ac
void UnkType_10c18ec0::SwapUnk9ac(int First, int Second)
{
    int Temp = unk_9ac[First];
    unk_9ac[First] = unk_9ac[Second];
    unk_9ac[Second] = Temp;
}
