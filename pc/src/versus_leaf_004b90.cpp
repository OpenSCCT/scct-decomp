// versus_leaf_004b90.cpp -- the function at file offset 0x4b90, VA 0x10904b90, 11 bytes. It stores
// its int argument at +0x00 of the object and returns the object pointer.
// The class and method names are invented; the offset and the bytes are the binary's.

class UnkType_10904b90
{
public:
    UnkType_10904b90 *SetUnk00(int Value);

private:
    int unk_00;
};

// UnkType_10904b90::SetUnk00
UnkType_10904b90 *UnkType_10904b90::SetUnk00(int Value)
{
    unk_00 = Value;
    return this;
}
