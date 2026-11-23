// campaign_leaf_4a23a0.cpp -- one function at file offset 0x4a23a0, preferred VA 0x10da23a0.
// It deletes the object at offset 0x38 through its destructor at 0x10d9d610 and the operator
// delete at 0x10d87b90 and clears the pointer. The class, method and member names are invented;
// the offset and the bytes are the binary's.

class UnkType_10da23a0_Item
{
public:
    int unk_0;

    ~UnkType_10da23a0_Item();
};

class UnkType_10da23a0
{
public:
    unsigned char unk_0[0x38];
    UnkType_10da23a0_Item* unk_38;

    void Unk_10da23a0();
};

// UnkType_10da23a0::Unk_10da23a0
void UnkType_10da23a0::Unk_10da23a0()
{
    delete unk_38;
    unk_38 = 0;
}
