// versus_leaf_259520.cpp -- returns the pointer at 0 advanced by 8 bytes, at file offset 0x259520 (VA 0x10b59520).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b59520
{
public:
    unsigned char *GetUnk00Plus08();

private:
    unsigned char *unk_00;              // advanced by GetUnk00Plus08
};

// UnkType_10b59520::GetUnk00Plus08
unsigned char *UnkType_10b59520::GetUnk00Plus08()
{
    return unk_00 + 8;
}
