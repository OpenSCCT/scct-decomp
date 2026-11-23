// campaign_leaf_71a6b0.cpp -- one function at file offset 0x71a6b0, preferred VA 0x1101a6b0. It
// passes its argument to the method at VA 0x10e6d000 of the member at 0x0 and then to the method
// at VA 0x1101e7d0 of the member at 0x20. The class, method and member names are invented; the
// offsets and the addresses are the binary's.

class UnkType_10e6d000
{
public:
    void Unk_10e6d000(void* Arg);

    unsigned char unk_0[0x20];
};

class UnkType_1101e7d0
{
public:
    void Unk_1101e7d0(void* Arg);
};

class UnkType_1101a6b0
{
public:
    void Unk_1101a6b0(void* Arg);

    UnkType_10e6d000 unk_0;
    UnkType_1101e7d0 unk_20;
};

// UnkType_1101a6b0::Unk_1101a6b0
void UnkType_1101a6b0::Unk_1101a6b0(void* Arg)
{
    unk_0.Unk_10e6d000(Arg);
    unk_20.Unk_1101e7d0(Arg);
}
