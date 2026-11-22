// versus_leaf_238ba0.cpp -- clears the int at 0 of the object, at file offset 0x238ba0 (VA 0x10b38ba0).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b38ba0
{
public:
    void ClearUnk00();

private:
    int unk_00;                         // cleared by ClearUnk00
};

// UnkType_10b38ba0::ClearUnk00
void UnkType_10b38ba0::ClearUnk00()
{
    unk_00 = 0;
}
