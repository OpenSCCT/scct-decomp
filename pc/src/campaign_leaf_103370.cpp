// campaign_leaf_103370.cpp -- one function at file offset 0x103370, preferred VA 0x10a03370. It
// sets bit 0x10 of the flags at offset 0x2c0 and stores its 12-byte by-value argument at offset
// 0x2c4. The class, method and member names are invented; the offset and the bytes are the
// binary's.

struct UnkType_10a03370_Triple
{
    int unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10a03370
{
public:
    unsigned char unk_0[0x2c0];
    int unk_2c0;
    UnkType_10a03370_Triple unk_2c4;

    void Unk_10a03370(UnkType_10a03370_Triple Value);
};

// UnkType_10a03370::Unk_10a03370
void UnkType_10a03370::Unk_10a03370(UnkType_10a03370_Triple Value)
{
    unk_2c0 |= 0x10;
    unk_2c4 = Value;
}
