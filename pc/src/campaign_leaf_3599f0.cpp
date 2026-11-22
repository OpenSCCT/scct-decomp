// campaign_leaf_3599f0.cpp -- one function at file offset 0x3599f0, preferred VA 0x10c599f0. It
// returns by value the three-word structure at offset 0xe8 of the object the pointer at 0x57c
// points to. The class, method, structure and member names are invented; the offsets and the
// bytes are the binary's.

struct UnkType_10c599f0_Triple
{
    int unk_0;
    int unk_4;
    int unk_8;
};

struct UnkType_10c599f0_Owner
{
    unsigned char unk_0[0xe8];
    UnkType_10c599f0_Triple unk_e8;
};

class UnkType_10c599f0
{
public:
    UnkType_10c599f0_Triple GetUnk57cE8() const;

    unsigned char unk_0[0x57c];
    UnkType_10c599f0_Owner* unk_57c;
};

// UnkType_10c599f0::GetUnk57cE8
UnkType_10c599f0_Triple UnkType_10c599f0::GetUnk57cE8() const
{
    return unk_57c->unk_e8;
}
