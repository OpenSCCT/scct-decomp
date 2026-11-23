// campaign_leaf_4c74f0.cpp -- method at VA 0x10dc74f0: returns Scale times the unsigned result of
// the method at VA 0x10dc73d0 for 0x10000, divided by 65536. The class, method and parameter names
// are invented; the constants and the address are the binary's.

class UnkType_10dc74f0
{
public:
    unsigned int Unk_10dc73d0(unsigned int Range);
    float Unk_10dc74f0(float Scale);
};

// UnkType_10dc74f0::Unk_10dc74f0
float UnkType_10dc74f0::Unk_10dc74f0(float Scale)
{
    return Scale * ( Unk_10dc73d0(0x10000) / 65536.0f );
}
