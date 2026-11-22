// campaign_leaf_5ec260.cpp -- stdcall function at VA 0x10eec260: returns false for a null object;
// otherwise passes its second argument to the ninth virtual method of the object and returns true.
// All names are invented.

class UnkType_10eec260
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8(int Value);
};

// Unk_10eec260
bool __stdcall Unk_10eec260(UnkType_10eec260* Object, int Value)
{
    if ( !Object )
    {
        return false;
    }
    Object->VirtualSlot8(Value);
    return true;
}
