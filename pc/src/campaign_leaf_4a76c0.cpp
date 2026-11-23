// campaign_leaf_4a76c0.cpp -- one function at file offset 0x4a76c0, preferred VA 0x10da76c0.
// It passes the int at offset 0x40 to the cdecl function at 0x10d98f20 and then Value to the
// method at 0x10dd65c0 of the member at offset 0x2c. The class, function, method and member names
// are invented; the offset and the bytes are the binary's.

void Unk_10d98f20(int Value);

class UnkType_10da76c0_Member
{
public:
    void Unk_10dd65c0(int Value);
};

class UnkType_10da76c0
{
public:
    unsigned char unk_0[0x2c];
    UnkType_10da76c0_Member unk_2c;
    unsigned char unk_2d[0x13];
    int unk_40;

    void Unk_10da76c0(int Value);
};

// UnkType_10da76c0::Unk_10da76c0
void UnkType_10da76c0::Unk_10da76c0(int Value)
{
    Unk_10d98f20(unk_40);
    unk_2c.Unk_10dd65c0(Value);
}
