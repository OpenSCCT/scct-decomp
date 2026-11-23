// campaign_leaf_71a690.cpp -- one function at file offset 0x71a690, preferred VA 0x1101a690. It
// passes its argument to the method at VA 0x10e6d010 of the member at 0x0 and then to the method
// at VA 0x1101e510 of the member at 0x20. The class, method and member names are invented; the
// offsets and the addresses are the binary's.

class UnkType_10e6d010
{
public:
    void Unk_10e6d010(void* Arg);

    unsigned char unk_0[0x20];
};

class UnkType_1101e510
{
public:
    void Unk_1101e510(void* Arg);
};

class UnkType_1101a690
{
public:
    void Unk_1101a690(void* Arg);

    UnkType_10e6d010 unk_0;
    UnkType_1101e510 unk_20;
};

// UnkType_1101a690::Unk_1101a690
void UnkType_1101a690::Unk_1101a690(void* Arg)
{
    unk_0.Unk_10e6d010(Arg);
    unk_20.Unk_1101e510(Arg);
}
