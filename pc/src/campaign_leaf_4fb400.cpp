// campaign_leaf_4fb400.cpp -- function at VA 0x10dfb400: writes the three words at 0x04 to 0x0c of
// its second argument to the stream that is its first (method at VA 0x10d9e850). The function,
// class and member names are invented; the offsets and the addresses are the binary's.

class UnkType_10dfb400_Writer
{
public:
    void Unk_10d9e810(unsigned short Value);
    void Unk_10d9e850(int Value);
};

class UnkType_10dfb400_Object
{
public:
    unsigned char unk_00[0x04];
    int unk_04;
    int unk_08;
    int unk_0c;
};

// Unk_10dfb400
void Unk_10dfb400(UnkType_10dfb400_Writer* Writer, const UnkType_10dfb400_Object* Object)
{
    Writer->Unk_10d9e850(Object->unk_04);
    Writer->Unk_10d9e850(Object->unk_08);
    Writer->Unk_10d9e850(Object->unk_0c);
}
