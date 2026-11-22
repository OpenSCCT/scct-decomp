// campaign_leaf_06a2b0.cpp -- one function at file offset 0x06a2b0, preferred VA 0x1096a2b0. It
// stores the word at offset 0x48 of this object through its pointer argument, and returns that
// pointer. The class, method and parameter names are invented; the offset and the bytes are the
// binary's.

class UnkType_1096a2b0
{
public:
    int *GetUnk48(int *Out) const;

private:
    unsigned char unk_00[0x48];     // not read by this function
    int unk_48;
};

// UnkType_1096a2b0::GetUnk48
int *UnkType_1096a2b0::GetUnk48(int *Out) const
{
    *Out = unk_48;
    return Out;
}
