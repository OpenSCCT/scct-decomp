// versus_leaf_16b370.cpp -- returns the int member at 0x4c of the object, ignoring its argument, at file offset 0x16b370 (VA 0x10a6b370).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10a6b370
{
public:
    int GetUnk4C(int Unused);

private:
    unsigned char unk_00[0x4c];  // not read by this function
    int unk_4c;        // read by GetUnk4C
};

// UnkType_10a6b370::GetUnk4C
// Unused is never read; the function pops its one argument (ret 4).
int UnkType_10a6b370::GetUnk4C(int Unused)
{
    return unk_4c;
}
