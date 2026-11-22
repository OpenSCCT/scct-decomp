// campaign_leaf_0af820.cpp -- one function at file offset 0xaf820, preferred VA 0x109af820. It
// returns by value the 12-byte value at offset 0xe8 of the object at offset 0x44c, or of its own
// object when that pointer is null. It pops one more argument it never reads. The class, method
// and member names are invented; the offset and the bytes are the binary's.

struct UnkType_109af820_Triple
{
    int unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_109af820
{
public:
    unsigned char unk_0[0xe8];
    UnkType_109af820_Triple unk_e8;
    unsigned char unk_f4[0x44c - 0xf4];
    UnkType_109af820* unk_44c;

    UnkType_109af820_Triple Unk_109af820(int Unused) const;
};

// UnkType_109af820::Unk_109af820
UnkType_109af820_Triple UnkType_109af820::Unk_109af820(int Unused) const
{
    if ( unk_44c )
    {
        return unk_44c->unk_e8;
    }
    return unk_e8;
}
