// campaign_leaf_337d20.cpp -- a member function at VA 0x10c37d20: when the pointer at 0x00 is not
// null it passes it to the free function at VA 0x109014a0 and clears it. guess: frees an owned
// block. The class, method and member names are invented; the offsets and addresses are the
// binary's.

void Unk_109014a0(void* Data);

class UnkType_10c37d20
{
public:
    void Unk_10c37d20();

private:
    void* unk_00;
};

// UnkType_10c37d20::Unk_10c37d20
void UnkType_10c37d20::Unk_10c37d20()
{
    if ( unk_00 )
    {
        Unk_109014a0(unk_00);
        unk_00 = 0;
    }
}
