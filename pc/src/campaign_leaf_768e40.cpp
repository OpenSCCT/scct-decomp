// campaign_leaf_768e40.cpp -- one function at file offset 0x768e40, preferred VA 0x11068e40. Given a
// pointer to an object pointer, it deletes the object through its virtual destructor (vtable slot
// 16, called with the deleting flag 1) when the pointer is set, and clears the pointer. It has no
// this pointer. The class and function names are invented; the offset and the slot are the
// binary's.

class UnkType_11068e40
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
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual ~UnkType_11068e40();
};

// Unk_11068e40
void Unk_11068e40(UnkType_11068e40** Object)
{
    if ( *Object != 0 )
    {
        delete *Object;
        *Object = 0;
    }
}
