// campaign_band2_counter_5c.cpp -- increments the counter at offset 0x5c. The class and method
// names are invented; the offset is the binary's.

class UnkType_10c2f010
{
public:
    void IncrementUnk5c();

private:
    unsigned char unk_00[0x5c];    // not read by any function in this unit
    int unk_5c;
};

// UnkType_10c2f010::IncrementUnk5c
void UnkType_10c2f010::IncrementUnk5c()
{
    unk_5c++;
}
