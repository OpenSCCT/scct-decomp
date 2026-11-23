// campaign_leaf_768470.cpp -- one function at file offset 0x768470, preferred VA 0x11068470. It
// passes its argument to the method at VA 0x1105ef10 and, when that returns nonzero, stores 2 in
// the word at 0x10. The class, method and member names are invented; the offsets and the callee's
// address are the binary's.

class UnkType_11068470
{
public:
    int Unk_1105ef10(void* Arg);
    void Unk_11068470(void* Arg);

    unsigned char unk_0[0x10];
    int unk_10;
};

// UnkType_11068470::Unk_11068470
void UnkType_11068470::Unk_11068470(void* Arg)
{
    if ( Unk_1105ef10(Arg) )
    {
        unk_10 = 2;
    }
}
