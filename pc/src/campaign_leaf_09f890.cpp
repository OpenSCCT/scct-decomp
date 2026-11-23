// campaign_leaf_09f890.cpp -- method at VA 0x1099f890: stores its second argument at 0x38; if it is
// not null, calls the method at VA 0x1099f590 on the object it points to with the first argument.
// The class, member and method names are invented; the offsets and the address are the binary's.

class UnkType_1099f890_1099f590
{
public:
    void Unk_1099f590(int Value);
};

class UnkType_1099f890
{
public:
    void Unk_1099f890(int Value, UnkType_1099f890_1099f590* Target);

private:
    unsigned char unk_00[0x38];
    UnkType_1099f890_1099f590* unk_38;
};

// UnkType_1099f890::Unk_1099f890
void UnkType_1099f890::Unk_1099f890(int Value, UnkType_1099f890_1099f590* Target)
{
    unk_38 = Target;
    if ( Target )
    {
        Target->Unk_1099f590(Value);
    }
}
