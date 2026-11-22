// campaign_band2_counter_0c.cpp -- decrements the counter at offset 0xc. The class and method names
// are invented; the offset is the binary's.

class UnkType_10dcde80
{
public:
    void DecrementUnk0c();

private:
    unsigned char unk_00[0xc];    // not read by any function in this unit
    int unk_0c;
};

// UnkType_10dcde80::DecrementUnk0c
void UnkType_10dcde80::DecrementUnk0c()
{
    unk_0c--;
}
