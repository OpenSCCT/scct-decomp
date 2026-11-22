// campaign_leaf_42bd40.cpp -- thiscall at VA 0x10d2bd40: calls the method at VA 0x10d339c0 of its
// argument; when bit 1 of the byte at offset 0xb4 is set, calls the methods at VA 0x10d2b210 and
// 0x10d2b180 with -1 and, when the byte at offset 0xb6 is set, the method at VA 0x10d2a830 with
// -1, 0 and 0; returns whether bit 1 is clear. All names are invented.

class UnkType_10d339c0
{
public:
    void Unk_10d339c0();
};

class UnkType_10d2bd40
{
public:
    void Unk_10d2a830(int Index, int First, int Second);
    void Unk_10d2b180(int Index);
    void Unk_10d2b210(int Index);
    bool Unk_10d2bd40(UnkType_10d339c0* Object);

private:
    unsigned char unk_00[0xb4];
    unsigned char unk_b4;
    unsigned char unk_b5;
    unsigned char unk_b6;
};

// UnkType_10d2bd40::Unk_10d2bd40
bool UnkType_10d2bd40::Unk_10d2bd40(UnkType_10d339c0* Object)
{
    Object->Unk_10d339c0();
    if (unk_b4 & 2) {
        Unk_10d2b210(-1);
        Unk_10d2b180(-1);
        if (unk_b6) {
            Unk_10d2a830(-1, 0, 0);
        }
    }
    return !(unk_b4 & 2);
}
