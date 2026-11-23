// campaign_leaf_4fa820.cpp -- function at VA 0x10dfa820: writes the six words at 0x04 to 0x18 of
// its second argument to the stream that is its first (method at VA 0x10d9e850). The function,
// class and member names are invented; the offsets and the addresses are the binary's.

class UnkType_10dfa820_Writer
{
public:
    void Unk_10d9e810(unsigned short Value);
    void Unk_10d9e850(int Value);
};

class UnkType_10dfa820_Object
{
public:
    unsigned char unk_00[0x04];
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
    int unk_18;
};

// Unk_10dfa820
void Unk_10dfa820(UnkType_10dfa820_Writer* Writer, const UnkType_10dfa820_Object* Object)
{
    Writer->Unk_10d9e850(Object->unk_04);
    Writer->Unk_10d9e850(Object->unk_08);
    Writer->Unk_10d9e850(Object->unk_0c);
    Writer->Unk_10d9e850(Object->unk_10);
    Writer->Unk_10d9e850(Object->unk_14);
    Writer->Unk_10d9e850(Object->unk_18);
}
