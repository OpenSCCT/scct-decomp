// versus_leaf_29f570.cpp -- stores a dword and two bytes from its three arguments at 0, 4 and 5, and returns the
// object, at file offset 0x29f570 (VA 0x10b9f570). The class and method names are invented; the offsets, the
// argument sizes and the calling convention are the binary's.

class UnkType_10b9f570
{
public:
    UnkType_10b9f570 *SetUnk00Unk04Unk05(int Dword, unsigned char Byte4, unsigned char Byte5);

private:
    int unk_00;                         // written by SetUnk00Unk04Unk05
    unsigned char unk_04;               // written by SetUnk00Unk04Unk05
    unsigned char unk_05;               // written by SetUnk00Unk04Unk05
};

// UnkType_10b9f570::SetUnk00Unk04Unk05
// Returns this in EAX; the function pops its three arguments (ret 0xc).
UnkType_10b9f570 *UnkType_10b9f570::SetUnk00Unk04Unk05(int Dword, unsigned char Byte4, unsigned char Byte5)
{
    unk_00 = Dword;
    unk_04 = Byte4;
    unk_05 = Byte5;
    return this;
}
