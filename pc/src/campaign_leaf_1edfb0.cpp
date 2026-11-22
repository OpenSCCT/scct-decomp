// campaign_leaf_1edfb0.cpp -- copies the dword at offset 0x0c of this to the int that the argument
// points to, and returns that pointer. File offset 0x1edfb0, VA 0x10aedfb0. The class and method
// names are invented; the offsets are the binary's. The return value is a guess.

class UnkType_10aedfb0
{
public:
    int *UnkMethod_10aedfb0(int *out);

private:
    unsigned char unk_00[0x0c];     // not read by this function
    int unk_0c;
};

// UnkType_10aedfb0::UnkMethod_10aedfb0
int *UnkType_10aedfb0::UnkMethod_10aedfb0(int *out)
{
    *out = unk_0c;
    return out;
}
