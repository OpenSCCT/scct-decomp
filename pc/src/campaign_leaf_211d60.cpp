// campaign_leaf_211d60.cpp -- a member function at VA 0x10b11d60 that stores in the int at 0x00 the
// result of the free function at VA 0x10eaad24, given the address of the function at VA 0x10ad0be0,
// and passes it to the member at VA 0x10b11700. The class, method and member names are invented;
// the offsets and addresses are the binary's.

void Unk_10ad0be0();
int Unk_10eaad24(void (*Callback)());

class UnkType_10b11d60
{
public:
    void Unk_10b11700(int Value);
    void Unk_10b11d60();

private:
    int unk_00;
};

// UnkType_10b11d60::Unk_10b11d60
void UnkType_10b11d60::Unk_10b11d60()
{
    unk_00 = Unk_10eaad24(Unk_10ad0be0);
    Unk_10b11700(unk_00);
}
