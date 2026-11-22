// campaign_band2_flag_00.cpp -- set and clear the byte flag at offset 0, from the functions at VA
// 0x10df5670 and 0x10df5680. The class and method names are invented; the offset is the binary's.

class UnkType_10df5670
{
public:
    void SetUnk00();
    void ClearUnk00();

private:
    unsigned char unk_00;
};

// UnkType_10df5670::SetUnk00
void UnkType_10df5670::SetUnk00()
{
    unk_00 = 1;
}

// UnkType_10df5670::ClearUnk00
void UnkType_10df5670::ClearUnk00()
{
    unk_00 = 0;
}
