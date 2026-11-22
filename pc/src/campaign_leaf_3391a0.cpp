// campaign_leaf_3391a0.cpp -- a member function at VA 0x10c391a0: when the pointer at 0x00 is not
// null it passes it to the free function at VA 0x109014a0 and clears it. guess: frees an owned
// block. The class, method and member names are invented; the offsets and addresses are the
// binary's.

void Unk_109014a0(void* Data);

class UnkType_10c391a0
{
public:
    void Unk_10c391a0();

private:
    void* unk_00;
};

// UnkType_10c391a0::Unk_10c391a0
void UnkType_10c391a0::Unk_10c391a0()
{
    if ( unk_00 )
    {
        Unk_109014a0(unk_00);
        unk_00 = 0;
    }
}
