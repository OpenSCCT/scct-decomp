// campaign_band2_byte_flags.cpp -- methods on two leading byte fields of one class, from the
// functions at VA 0x10dbbd90-0x10dbbdc0. The class and method names are invented; the offsets are
// the binary's.

class UnkType_10dbbd90
{
public:
    unsigned char GetUnk01();
    unsigned char GetUnk00();
    void SetUnk00();
    unsigned char AlwaysTrue();

private:
    unsigned char unk_00;
    unsigned char unk_01;
};

// UnkType_10dbbd90::GetUnk01
unsigned char UnkType_10dbbd90::GetUnk01()
{
    return unk_01;
}

// UnkType_10dbbd90::GetUnk00
unsigned char UnkType_10dbbd90::GetUnk00()
{
    return unk_00;
}

// UnkType_10dbbd90::SetUnk00
//
// Sets the byte at offset 0 to 1.
void UnkType_10dbbd90::SetUnk00()
{
    unk_00 = 1;
}

// UnkType_10dbbd90::AlwaysTrue
//
// guess: a member of this class, from its place beside the others; it returns 1 and reads nothing.
unsigned char UnkType_10dbbd90::AlwaysTrue()
{
    return 1;
}
