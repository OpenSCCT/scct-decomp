// campaign_band2_counter_24.cpp -- a counter at offset 0x24, raised by one method and read by the
// next. The class and method names are invented; the offset is the binary's.

class UnkType_10e073f0
{
public:
    void IncrementUnk24();
    int GetUnk24();

private:
    unsigned char unk_00[0x24];    // not read by any function in this unit
    int unk_24;
};

// UnkType_10e073f0::IncrementUnk24
void UnkType_10e073f0::IncrementUnk24()
{
    unk_24++;
}

// UnkType_10e073f0::GetUnk24
int UnkType_10e073f0::GetUnk24()
{
    return unk_24;
}
