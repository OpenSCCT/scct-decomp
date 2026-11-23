// campaign_leaf_4c2ff0.cpp -- one function at file offset 0x4c2ff0, preferred VA 0x10dc2ff0.
// While the count at offset 0x20 is non-zero it passes the object held by the first node of the
// list headed at offset 0x1c to the method at 0x10dc2f80; then it returns true. The class,
// structure, method and member names are invented; the offset and the bytes are the binary's.

struct UnkType_10dc2ff0_Node
{
    UnkType_10dc2ff0_Node* unk_0;
    UnkType_10dc2ff0_Node* unk_4;
    void* unk_8;
};

class UnkType_10dc2ff0
{
public:
    unsigned char unk_0[0x1c];
    UnkType_10dc2ff0_Node* unk_1c;
    int unk_20;

    void Unk_10dc2f80(void* Item);
    bool Unk_10dc2ff0();
};

// UnkType_10dc2ff0::Unk_10dc2ff0
bool UnkType_10dc2ff0::Unk_10dc2ff0()
{
    while ( unk_20 != 0 )
    {
        Unk_10dc2f80(unk_1c->unk_0->unk_8);
    }
    return true;
}
