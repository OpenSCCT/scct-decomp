// campaign_leaf_267670.cpp -- a member function at VA 0x10b67670 that passes its first argument and
// the ints at 0x164 and 0x168 to the member at VA 0x10b668a0. It does not read its second argument.
// The class, method and member names are invented; the offsets and addresses are the binary's.

class UnkType_10b67670
{
public:
    void Unk_10b668a0(int Value, int First, int Second);
    void Unk_10b67670(int Value, int Unused);

private:
    unsigned char unk_000[0x164];
    int unk_164;
    int unk_168;
};

// UnkType_10b67670::Unk_10b67670
void UnkType_10b67670::Unk_10b67670(int Value, int Unused)
{
    Unk_10b668a0(Value, unk_164, unk_168);
}
