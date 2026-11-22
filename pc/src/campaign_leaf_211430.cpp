// campaign_leaf_211430.cpp -- a member function at VA 0x10b11430 that passes the int at 0x00 and
// the address of the function at VA 0x10ad0c00 to the free function at VA 0x10eaab80, then clears
// the int. The class, method and member names are invented; the offsets and addresses are the
// binary's.

void Unk_10ad0c00();
void Unk_10eaab80(int Value, void (*Callback)());

class UnkType_10b11430
{
public:
    void Unk_10b11430();

private:
    int unk_00;
};

// UnkType_10b11430::Unk_10b11430
void UnkType_10b11430::Unk_10b11430()
{
    Unk_10eaab80(unk_00, Unk_10ad0c00);
    unk_00 = 0;
}
