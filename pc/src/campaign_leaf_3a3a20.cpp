// campaign_leaf_3a3a20.cpp -- a member function at VA 0x10ca3a20 that calls the member at VA
// 0x10ca3830 and then passes the pointer at 0x14 to the free function at VA 0x109014a0. The class,
// method and member names are invented; the offsets and addresses are the binary's.

void Unk_109014a0(void* Data);

class UnkType_10ca3a20
{
public:
    void Unk_10ca3830();
    void Unk_10ca3a20();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    void* unk_14;
};

// UnkType_10ca3a20::Unk_10ca3a20
void UnkType_10ca3a20::Unk_10ca3a20()
{
    Unk_10ca3830();
    Unk_109014a0(unk_14);
}
