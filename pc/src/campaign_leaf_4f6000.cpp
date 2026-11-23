// campaign_leaf_4f6000.cpp -- method at VA 0x10df6000: calls the method at VA 0x10d9df90 on its
// first argument with the address of each of the six 0x154-byte entries at 0x04. The class, method
// and member names are invented; the offsets and the address are the binary's.

class UnkType_10df6000_Entry
{
public:
    int unk_00;
    unsigned char unk_04[0x150];
};

class UnkType_10df6000_Target
{
public:
    void Unk_10d9df90(UnkType_10df6000_Entry* Entry);
};

class UnkType_10df6000
{
public:
    void Unk_10df6000(UnkType_10df6000_Target* Target);

    int unk_00;
    UnkType_10df6000_Entry unk_04[6];
};

// UnkType_10df6000::Unk_10df6000
void UnkType_10df6000::Unk_10df6000(UnkType_10df6000_Target* Target)
{
    Target->Unk_10d9df90(&unk_04[0]);
    Target->Unk_10d9df90(&unk_04[1]);
    Target->Unk_10d9df90(&unk_04[2]);
    Target->Unk_10d9df90(&unk_04[3]);
    Target->Unk_10d9df90(&unk_04[4]);
    Target->Unk_10d9df90(&unk_04[5]);
}
