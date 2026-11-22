// campaign_band2_flag_06.cpp -- set and clear the byte flag at offset 6, from the functions at VA
// 0x10df5690 and 0x10df56a0. Both callers of the setter (VA 0x10df1d50 and 0x10df2180) first store
// a word at offset 0 of the same object. The class and method names are invented; the offsets are
// the binary's.

class UnkType_10df5690
{
public:
    unsigned char SetUnk06();
    void ClearUnk06();

private:
    int unk_00;                 // stored by both callers of SetUnk06
    unsigned char unk_04[2];    // not read by any function in this unit
    unsigned char unk_06;
};

// UnkType_10df5690::SetUnk06
//
// Sets the flag and returns 1: the retail code stores it from AL, the return register.
unsigned char UnkType_10df5690::SetUnk06()
{
    unk_06 = 1;
    return 1;
}

// UnkType_10df5690::ClearUnk06
void UnkType_10df5690::ClearUnk06()
{
    unk_06 = 0;
}
