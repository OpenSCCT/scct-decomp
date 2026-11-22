// versus_leaf_252b00.cpp -- returns the pointer at 0 advanced by 0x10 bytes, at file offset 0x252b00 (VA 0x10b52b00).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b52b00
{
public:
    unsigned char *GetUnk00Plus10();

private:
    unsigned char *unk_00;              // advanced by GetUnk00Plus10
};

// UnkType_10b52b00::GetUnk00Plus10
unsigned char *UnkType_10b52b00::GetUnk00Plus10()
{
    return unk_00 + 0x10;
}
