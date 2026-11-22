// versus_leaf_24b640.cpp -- clears the ints at 0, 4 and 8; the argument is never read, at file offset 0x24b640 (VA 0x10b4b640).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b4b640
{
public:
    UnkType_10b4b640 &ClearUnk00To08(int Unused);

private:
    int unk_00;                         // cleared by ClearUnk00To08
    int unk_04;                         // cleared by ClearUnk00To08
    int unk_08;                         // cleared by ClearUnk00To08
};

// UnkType_10b4b640::ClearUnk00To08
// Unused is never read; the function pops its one argument (ret 4).
UnkType_10b4b640 &UnkType_10b4b640::ClearUnk00To08(int Unused)
{
    unk_08 = unk_04 = unk_00 = 0;
    return *this;
}
