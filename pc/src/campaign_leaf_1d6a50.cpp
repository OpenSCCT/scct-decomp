// campaign_leaf_1d6a50.cpp -- returns the address of the inline buffer of the 60-byte item at the
// index argument of the array at offset 0x6c of this when its unsigned count at offset 0x18 is below
// 8, otherwise the pointer stored in the first dword of that buffer. File offset 0x1d6a50, VA
// 0x10ad6a50. The class and method names are invented; the offsets are the binary's. The item
// layout, the count and the union are guesses from the code.

class UnkType_10ad6a50Item
{
public:
    unsigned char unk_00[0x04];     // not read by this function
    union
    {
        unsigned char inline_buf[0x14];
        void *heap;
    } unk_04;
    unsigned int unk_18;
    unsigned char unk_1c[0x3c - 0x1c];  // not read by this function
};

class UnkType_10ad6a50
{
public:
    void *UnkMethod_10ad6a50(short index);

private:
    unsigned char unk_00[0x6c];     // not read by this function
    UnkType_10ad6a50Item *unk_6c;
};

// UnkType_10ad6a50::UnkMethod_10ad6a50
void *UnkType_10ad6a50::UnkMethod_10ad6a50(short index)
{
    UnkType_10ad6a50Item *item = &unk_6c[index];
    if (item->unk_18 >= 8)
        return item->unk_04.heap;
    return item->unk_04.inline_buf;
}
