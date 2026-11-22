// versus_leaf_130490.cpp -- the function at file offset 0x130490, VA 0x10a30490, 14 bytes. It returns 1
// when the object address equals its first argument, and 0 otherwise (ret 0xc: three stack arguments).
// The second and third arguments are pushed by callers and never read.
// The class and method names are invented; the offset and the bytes come from the binary.

class UnkType_10a30490
{
public:
    int UnkFunc_10a30490(UnkType_10a30490 *Other, int Unused1, int Unused2);
};

// UnkType_10a30490::UnkFunc_10a30490
int UnkType_10a30490::UnkFunc_10a30490(UnkType_10a30490 *Other, int Unused1, int Unused2)
{
    return this == Other;
}
