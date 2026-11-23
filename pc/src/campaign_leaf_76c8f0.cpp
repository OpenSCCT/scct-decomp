// campaign_leaf_76c8f0.cpp -- one function at file offset 0x76c8f0, preferred VA 0x1106c8f0. It
// calls the method at VA 0x1106cdf0 on the object at 0x30 and the method at VA 0x110712d0 on the
// object at 0x24. The class, method and member names are invented; the offset and the addresses
// are the binary's.

class UnkType_1106cdf0
{
public:
    void Unk_1106cdf0();
};

class UnkType_110712d0
{
public:
    void Unk_110712d0();
};

class UnkType_1106c8f0
{
public:
    void Unk_1106c8f0();

    unsigned char unk_0[0x24];
    UnkType_110712d0* unk_24;
    unsigned char unk_28[0x30 - 0x28];
    UnkType_1106cdf0* unk_30;
};

// UnkType_1106c8f0::Unk_1106c8f0
void UnkType_1106c8f0::Unk_1106c8f0()
{
    unk_30->Unk_1106cdf0();
    unk_24->Unk_110712d0();
}
