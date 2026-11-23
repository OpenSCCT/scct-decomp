// campaign_leaf_3e9460.cpp -- method at VA 0x10ce9460: returns whether the float First points to
// equals the float Second points to, or zero when Second is null. It does not read its this
// pointer. The class, method and parameter names are invented; the bytes are the binary's.

class UnkType_10ce9460
{
public:
    int Unk_10ce9460(float* First, float* Second);
};

// UnkType_10ce9460::Unk_10ce9460
int UnkType_10ce9460::Unk_10ce9460(float* First, float* Second)
{
    return *First == ( Second ? *Second : 0.0f );
}
