// versus_leaf_12a280.cpp -- the function at file offset 0x12a280, VA 0x10a2a280, 30 bytes. It increments
// the dword at +0x0c of its first argument, then stores 1 at the int that its second argument points
// to when the byte at +0x2d2 of the object is 0x16, and 0 otherwise (ret 8).
// The class and method names are invented; the offset and the bytes come from the binary.

class UnkRef_10a2a280
{
public:
    unsigned char unk_00[0xc];      // not read by this function
    int unk_0c;
};

class UnkType_10a2a280
{
public:
    void UnkFunc_10a2a280(UnkRef_10a2a280 *Ref, int *Result);

private:
    unsigned char unk_00[0x2d2];    // not read by this function
    unsigned char unk_2d2;
};

// UnkType_10a2a280::UnkFunc_10a2a280
void UnkType_10a2a280::UnkFunc_10a2a280(UnkRef_10a2a280 *Ref, int *Result)
{
    bool Flag;
    ++Ref->unk_0c;
    Flag = unk_2d2 == 0x16;
    *Result = Flag;
}
