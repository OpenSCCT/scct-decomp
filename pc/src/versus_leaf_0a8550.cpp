// versus_leaf_0a8550.cpp -- the function at file offset 0xa8550, VA 0x109a8550, 10 bytes. It returns
// its second argument masked with 2 (ret 8: two stack arguments). The first argument is pushed by
// callers and never read.
// The class and method names are invented; the offset and the bytes come from the binary.

class UnkType_109a8550
{
public:
    int UnkFunc_109a8550(int Unused, int Flags);
};

// UnkType_109a8550::UnkFunc_109a8550
int UnkType_109a8550::UnkFunc_109a8550(int Unused, int Flags)
{
    return Flags & 2;
}
