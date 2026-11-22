// versus_leaf_2699e0.cpp -- clears Count dwords starting at Dest, at file offset 0x2699e0 (VA 0x10b699e0).
// The class and method names are invented; the argument sizes and the __stdcall convention are the binary's.

class UnkType_10b699e0
{
public:
    static void __stdcall ZeroUnkDwords(unsigned int *Dest, unsigned int Count);
};

// UnkType_10b699e0::ZeroUnkDwords
// The function pops its two arguments (ret 8).
void __stdcall UnkType_10b699e0::ZeroUnkDwords(unsigned int *Dest, unsigned int Count)
{
    for (unsigned int i = 0; i < Count; i++)
    {
        Dest[i] = 0;
    }
}
