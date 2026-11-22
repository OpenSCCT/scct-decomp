// campaign_band2_short_counter_c0.cpp -- a 16-bit counter at offset 0xc0, raised by one method and
// read by the next. The class and method names are invented; the offset is the binary's.

class UnkType_10de0aa0
{
public:
    void IncrementUnkC0();
    unsigned short GetUnkC0();

private:
    unsigned char unk_00[0xc0];    // not read by any function in this unit
    unsigned short unk_c0;
};

// UnkType_10de0aa0::IncrementUnkC0
void UnkType_10de0aa0::IncrementUnkC0()
{
    unk_c0++;
}

// UnkType_10de0aa0::GetUnkC0
unsigned short UnkType_10de0aa0::GetUnkC0()
{
    return unk_c0;
}
