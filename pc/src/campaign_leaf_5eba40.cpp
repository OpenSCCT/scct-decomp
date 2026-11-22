// campaign_leaf_5eba40.cpp -- stdcall function at VA 0x10eeba40: returns false for a null argument;
// otherwise calls the second virtual method of the argument and returns true. All names are
// invented.

class UnkType_10eeba40
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
};

// Unk_10eeba40
bool __stdcall Unk_10eeba40(UnkType_10eeba40* Object)
{
    if ( !Object )
    {
        return false;
    }
    Object->VirtualSlot1();
    return true;
}
