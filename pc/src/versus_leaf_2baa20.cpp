// versus_leaf_2baa20.cpp -- compares the int at 0x134 of the element at 0x6c with 4, at file offset 0x2baa20
// (VA 0x10bbaa20). The class, element and method names are invented; the offsets are the binary's.

struct UnkElement_10bbaa20
{
    unsigned char unk_00[0x134];
    int unk_134;                        // read by IsUnk134Four
};

class UnkType_10bbaa20
{
public:
    bool IsUnk134Four();

private:
    unsigned char unk_00[0x6c];
    UnkElement_10bbaa20 *unk_6c;
};

// UnkType_10bbaa20::IsUnk134Four
// Returns true when the element's int at 0x134 is 4.
bool UnkType_10bbaa20::IsUnk134Four()
{
    if (unk_6c->unk_134 == 4)
    {
        return true;
    }
    return false;
}
