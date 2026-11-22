// campaign_band2_flag_b8.cpp -- set, clear and read the byte flag at offset 0xb8, from the
// functions at VA 0x10d7d6d0-0x10d7d6f0. The class and method names are invented; the offset is
// the binary's.

class UnkType_10d7d6d0
{
public:
    void SetUnkB8();
    void ClearUnkB8();
    unsigned char GetUnkB8();

private:
    unsigned char unk_00[0xb8];     // not read by any function in this unit
    unsigned char unk_b8;
};

// UnkType_10d7d6d0::SetUnkB8
void UnkType_10d7d6d0::SetUnkB8()
{
    unk_b8 = 1;
}

// UnkType_10d7d6d0::ClearUnkB8
void UnkType_10d7d6d0::ClearUnkB8()
{
    unk_b8 = 0;
}

// UnkType_10d7d6d0::GetUnkB8
unsigned char UnkType_10d7d6d0::GetUnkB8()
{
    return unk_b8;
}
