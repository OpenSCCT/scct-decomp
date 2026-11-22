// versus_leaf_0a3f30.cpp -- the function at file offset 0xa3f30, VA 0x109a3f30, 23 bytes. It stores
// zero in the dword at each of its first two arguments (ret 0xc: three stack arguments). The third
// argument is pushed by callers and never read.
// The class and method names are invented; the offset and the bytes come from the binary.

class UnkType_109a3f30
{
public:
    void UnkFunc_109a3f30(int *First, int *Second, int Unused);
};

// UnkType_109a3f30::UnkFunc_109a3f30
void UnkType_109a3f30::UnkFunc_109a3f30(int *First, int *Second, int Unused)
{
    *Second = 0;
    *First = 0;
}
