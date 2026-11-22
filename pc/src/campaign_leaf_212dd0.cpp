// campaign_leaf_212dd0.cpp -- a free function at VA 0x10b12dd0 that allocates 0x48 bytes with the
// operator new at VA 0x10add0b0 (its second argument 0) and constructs an object there with the
// constructor at VA 0x10adc660, returning it or null. The class and function names are invented;
// the addresses and the size are the binary's.

void* operator new(unsigned int Size, int Flags);

class UnkType_10adc660
{
public:
    UnkType_10adc660();

private:
    unsigned char unk_00[0x48];
};

// Unk_10b12dd0
UnkType_10adc660* Unk_10b12dd0()
{
    return new(0) UnkType_10adc660;
}
