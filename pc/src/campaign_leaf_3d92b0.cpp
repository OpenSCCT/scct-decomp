// campaign_leaf_3d92b0.cpp -- a member function at VA 0x10cd92b0 that passes its two arguments to
// the member at VA 0x10cd7b30 and the result to the free function at VA 0x10cd8a10. The class,
// method and parameter names are invented; the addresses are the binary's.

int Unk_10cd8a10(int Value);

class UnkType_10cd92b0
{
public:
    int Unk_10cd7b30(int First, int Second);
    int Unk_10cd92b0(int First, int Second);
};

// UnkType_10cd92b0::Unk_10cd92b0
int UnkType_10cd92b0::Unk_10cd92b0(int First, int Second)
{
    return Unk_10cd8a10(Unk_10cd7b30(First, Second));
}
