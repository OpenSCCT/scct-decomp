// campaign_leaf_4fb430.cpp -- function at VA 0x10dfb430: reads the three words at 0x04 to 0x0c of
// its second argument from the stream that is its first (method at VA 0x10d9df90). The function,
// class and member names are invented; the offsets and the addresses are the binary's.

class UnkType_10dfb430_Reader
{
public:
    void Unk_10d9dd50(unsigned short* Value);
    void Unk_10d9df90(int* Value);
};

class UnkType_10dfb430_Object
{
public:
    unsigned char unk_00[0x04];
    int unk_04;
    int unk_08;
    int unk_0c;
};

// Unk_10dfb430
void Unk_10dfb430(UnkType_10dfb430_Reader* Reader, UnkType_10dfb430_Object* Object)
{
    Reader->Unk_10d9df90(&Object->unk_04);
    Reader->Unk_10d9df90(&Object->unk_08);
    Reader->Unk_10d9df90(&Object->unk_0c);
}
