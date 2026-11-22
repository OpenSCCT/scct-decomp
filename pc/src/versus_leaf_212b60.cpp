// versus_leaf_212b60.cpp -- returns the int member at 0x9c of the object, at file offset 0x212b60 (VA 0x10b12b60).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b12b60
{
public:
    int GetUnk9C();

private:
    unsigned char unk_00[0x9c];  // not read by this function
    int unk_9c;        // read by GetUnk9C
};

// UnkType_10b12b60::GetUnk9C
int UnkType_10b12b60::GetUnk9C()
{
    return unk_9c;
}
