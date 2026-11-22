// versus_leaf_2b7e90.cpp -- decrements the int at 0x5c and returns zero, at file offset 0x2b7e90 (VA 0x10bb7e90).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10bb7e90
{
public:
    int DecUnk5C();

private:
    unsigned char unk_00[0x5c];         // not read by this function
    int unk_5c;                         // decremented by DecUnk5C
};

// UnkType_10bb7e90::DecUnk5C
int UnkType_10bb7e90::DecUnk5C()
{
    --unk_5c;
    return 0;
}
