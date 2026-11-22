// campaign_leaf_5ec210.cpp -- stdcall function at VA 0x10eec210: returns false for a null object;
// otherwise passes its second argument to the seventh virtual method of the object and returns that
// method's result. All names are invented.

class UnkType_10eec210
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual bool VirtualSlot6(int Value);
};

// Unk_10eec210
bool __stdcall Unk_10eec210(UnkType_10eec210* Object, int Value)
{
    if ( !Object )
    {
        return false;
    }
    return Object->VirtualSlot6(Value);
}
