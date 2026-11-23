// campaign_leaf_4c7320.cpp -- one function at file offset 0x4c7320, preferred VA 0x10dc7320.
// The constructor installs the vtable at 0x11143e98 and passes the new object to the method at
// 0x10dc72c0 of what the function at 0x10dc7080 returns. The class, function and method names are
// invented; the offset and the bytes are the binary's.

class UnkType_10dc7320;

class UnkType_10dc7320_Callee
{
public:
    void Unk_10dc72c0(UnkType_10dc7320* Item);
};

UnkType_10dc7320_Callee* Unk_10dc7080();

class UnkType_10dc7320
{
public:
    UnkType_10dc7320();

    virtual void VirtualSlot0();
};

// UnkType_10dc7320::UnkType_10dc7320
UnkType_10dc7320::UnkType_10dc7320()
{
    Unk_10dc7080()->Unk_10dc72c0(this);
}
