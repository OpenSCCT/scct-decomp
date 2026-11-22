// campaign_leaf_49d630.cpp -- thiscall at VA 0x10d9d630: when its argument is not null, stores it
// at offset 0x2c and calls its first virtual method. All names are invented.

class UnkType_10d9d630_Obj
{
public:
    virtual void VirtualSlot0();
};

class UnkType_10d9d630
{
public:
    void Unk_10d9d630(UnkType_10d9d630_Obj* Object);

private:
    unsigned char unk_00[0x2c];
    UnkType_10d9d630_Obj* unk_2c;
};

// UnkType_10d9d630::Unk_10d9d630
void UnkType_10d9d630::Unk_10d9d630(UnkType_10d9d630_Obj* Object)
{
    if (Object) {
        unk_2c = Object;
        Object->VirtualSlot0();
    }
}
