// campaign_leaf_550e10.cpp -- one function at file offset 0x550e10, preferred VA 0x10e50e10. It
// copies the four ints of Value, one by one, into the object at offset 0xe0. The class, method,
// structure and member names are invented; the offset and the bytes are the binary's.

struct UnkType_10e50e10_Value
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
};

class UnkType_10e50e10
{
public:
    unsigned char unk_0[0xe0];
    UnkType_10e50e10_Value unk_e0;

    void SetUnkE0(const UnkType_10e50e10_Value& Value);
};

// UnkType_10e50e10::SetUnkE0
void UnkType_10e50e10::SetUnkE0(const UnkType_10e50e10_Value& Value)
{
    unk_e0.unk_0 = Value.unk_0;
    unk_e0.unk_4 = Value.unk_4;
    unk_e0.unk_8 = Value.unk_8;
    unk_e0.unk_c = Value.unk_c;
}
