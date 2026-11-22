// campaign_leaf_06b2d0.cpp -- one function at file offset 0x06b2d0, preferred VA 0x1096b2d0. It
// stores the word at offset 0x48 of this object through its pointer argument, and returns that
// pointer. The class, method and parameter names are invented; the offset and the bytes are the
// binary's.

class UnkType_1096b2d0
{
public:
    int *GetUnk48(int *Out) const;

private:
    unsigned char unk_00[0x48];     // not read by this function
    int unk_48;
};

// UnkType_1096b2d0::GetUnk48
int *UnkType_1096b2d0::GetUnk48(int *Out) const
{
    *Out = unk_48;
    return Out;
}
