// campaign_leaf_7634d0.cpp -- one function at file offset 0x7634d0, preferred VA 0x110634d0. It
// destroys the object its argument points to: the members at 0x74 and 0x78 that are set are
// released through the functions at VA 0x11062f30 and VA 0x11068e40 and cleared, the object is
// deleted (its destructor installs the vtable at VA 0x11176380, its operator delete is the
// function at VA 0x11067a10) and the pointer is cleared. The class and function names are
// invented; the offsets and the addresses are the binary's.

void Unk_11062f30(void** Member);
void Unk_11068e40(void** Member);

class UnkType_110634d0
{
public:
    static void operator delete(void* Object);

    ~UnkType_110634d0()
    {
    }

    virtual void VirtualSlot0();

    unsigned char unk_4[0x74 - 0x4];
    void* unk_74;
    void* unk_78;
};

// Unk_110634d0
void Unk_110634d0(UnkType_110634d0** Object)
{
    UnkType_110634d0* Current;

    Current = *Object;
    if ( Current != 0 )
    {
        if ( Current->unk_74 != 0 )
        {
            Unk_11062f30(&Current->unk_74);
            Current->unk_74 = 0;
        }
        if ( Current->unk_78 != 0 )
        {
            Unk_11068e40(&Current->unk_78);
            Current->unk_78 = 0;
        }
        delete *Object;
        *Object = 0;
    }
}
