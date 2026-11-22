// campaign_leaf_5a35f0.cpp -- one function at file offset 0x5a35f0, preferred VA 0x10ea35f0.
// It copies ten ints of Value into the object at offsets 0x10, 0xc and 0x14-0x30 (the inverse of
// the copy at 0x5a3540), then points the int at offset 8 of each of the seven objects at offsets
// 0x14-0x2c back at this object. The class, structure, method and member names are invented; the
// offset and the bytes are the binary's.

class UnkType_10ea35f0;

struct UnkType_10ea35f0_Node
{
    int unk_0;
    int unk_4;
    UnkType_10ea35f0* unk_8;
};

struct UnkType_10ea35f0_Value
{
    int unk_0;
    int unk_4;
    UnkType_10ea35f0_Node* unk_8;
    UnkType_10ea35f0_Node* unk_c;
    UnkType_10ea35f0_Node* unk_10;
    UnkType_10ea35f0_Node* unk_14;
    UnkType_10ea35f0_Node* unk_18;
    UnkType_10ea35f0_Node* unk_1c;
    UnkType_10ea35f0_Node* unk_20;
    int unk_24;
};

class UnkType_10ea35f0
{
public:
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    UnkType_10ea35f0_Node* unk_14;
    UnkType_10ea35f0_Node* unk_18;
    UnkType_10ea35f0_Node* unk_1c;
    UnkType_10ea35f0_Node* unk_20;
    UnkType_10ea35f0_Node* unk_24;
    UnkType_10ea35f0_Node* unk_28;
    UnkType_10ea35f0_Node* unk_2c;
    int unk_30;

    void Unk_10ea35f0(const UnkType_10ea35f0_Value& Value);
};

// UnkType_10ea35f0::Unk_10ea35f0
void UnkType_10ea35f0::Unk_10ea35f0(const UnkType_10ea35f0_Value& Value)
{
    unk_10 = Value.unk_0;
    unk_c = Value.unk_4;
    unk_14 = Value.unk_8;
    unk_18 = Value.unk_c;
    unk_1c = Value.unk_10;
    unk_20 = Value.unk_14;
    unk_24 = Value.unk_18;
    unk_28 = Value.unk_20;
    unk_2c = Value.unk_1c;
    unk_30 = Value.unk_24;
    unk_14->unk_8 = this;
    unk_18->unk_8 = this;
    unk_1c->unk_8 = this;
    unk_20->unk_8 = this;
    unk_24->unk_8 = this;
    unk_28->unk_8 = this;
    unk_2c->unk_8 = this;
}
