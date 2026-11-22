// campaign_band2_counters.cpp -- a counter at offset 0x1c, raised and lowered by two methods.
// The class and method names are invented; the offsets are the binary's.

class UnkType_10dd2770
{
public:
    void IncrementUnk1c();
    void DecrementUnk1c();

private:
    unsigned char unk_00[0x1c];     // not read by any function in this unit
    int unk_1c;
};

// UnkType_10dd2770::IncrementUnk1c
void UnkType_10dd2770::IncrementUnk1c()
{
    unk_1c++;
}

// UnkType_10dd2770::DecrementUnk1c
void UnkType_10dd2770::DecrementUnk1c()
{
    unk_1c--;
}
