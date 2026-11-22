// campaign_leaf_4ef140.cpp -- thiscall at VA 0x10def140: stores eight times the result of the
// method at VA 0x10dcddb0 of the object at offset 4 at offset 0x10. All names are invented.

class UnkType_10dcddb0
{
public:
    int Unk_10dcddb0();
};

class UnkType_10def140
{
public:
    void Unk_10def140();

private:
    int unk_00;
    UnkType_10dcddb0* unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
};

// UnkType_10def140::Unk_10def140
void UnkType_10def140::Unk_10def140()
{
    unk_10 = unk_04->Unk_10dcddb0() * 8;
}
