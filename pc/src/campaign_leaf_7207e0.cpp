// campaign_leaf_7207e0.cpp -- one function at file offset 0x7207e0, preferred VA 0x110207e0. It
// writes 2 to the byte it is given and calls the method at VA 0x110206b0; when that returns zero
// it writes 8 instead and calls the method at VA 0x11020710. The class, method and parameter
// names are invented; the offset and the addresses are the binary's.

class UnkType_110207e0
{
public:
    int Unk_110206b0();
    void Unk_11020710();
    void Unk_110207e0(unsigned char* State);
};

// UnkType_110207e0::Unk_110207e0
void UnkType_110207e0::Unk_110207e0(unsigned char* State)
{
    *State = 2;
    if ( Unk_110206b0() == 0 )
    {
        *State = 8;
        Unk_11020710();
    }
}
