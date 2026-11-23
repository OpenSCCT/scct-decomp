// campaign_leaf_4fa870.cpp -- function at VA 0x10dfa870: reads the six words at 0x04 to 0x18 of its
// second argument from the stream that is its first (method at VA 0x10d9df90). The function, class
// and member names are invented; the offsets and the addresses are the binary's.

class UnkType_10dfa870_Reader
{
public:
    void Unk_10d9dd50(unsigned short* Value);
    void Unk_10d9df90(int* Value);
};

class UnkType_10dfa870_Object
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

// Unk_10dfa870
void Unk_10dfa870(UnkType_10dfa870_Reader* Reader, UnkType_10dfa870_Object* Object)
{
    Reader->Unk_10d9df90(&Object->unk_04);
    Reader->Unk_10d9df90(&Object->unk_08);
    Reader->Unk_10d9df90(&Object->unk_0c);
    Reader->Unk_10d9df90(&Object->unk_10);
    Reader->Unk_10d9df90(&Object->unk_14);
    Reader->Unk_10d9df90(&Object->unk_18);
}
