// campaign_leaf_49cf60.cpp -- thiscall method at VA 0x10d9cf60. It passes the given source to the
// fourth virtual method of its object at 0x18 and to the method at 0x10dcdc10 of its object at
// 0x14, when present. When the source's method at 0x10dcde90 accepts 0, it calls the source's
// method at 0x10dcde80 and allocates a 0x30-byte object (tagged "TransportProtocol.cpp", line
// 0x3b) built from the source (0x10d9ec70). It returns the object when its method at 0x10d9e1b0
// returns true, else deletes it (destructor at 0x10d9d610) and returns null, as it does when the
// source refuses. The class, method and parameter names are invented.

void* operator new(unsigned int Size, const unsigned short* File, int Line);

class UnkType_10d9cf60_Source
{
public:
    bool Unk_10dcde90(int Value);
    void Unk_10dcde80();
};

class UnkType_10d9cf60_Listener
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3(UnkType_10d9cf60_Source* Source);
};

class UnkType_10d9cf60_Notified
{
public:
    void Unk_10dcdc10(UnkType_10d9cf60_Source* Source);
};

class UnkType_10d9cf60_Object
{
public:
    UnkType_10d9cf60_Object(UnkType_10d9cf60_Source* Source);
    ~UnkType_10d9cf60_Object();
    bool Unk_10d9e1b0();

private:
    unsigned char unk_0[0x30];
};

class UnkType_10d9cf60
{
public:
    UnkType_10d9cf60_Object* Unk_10d9cf60(UnkType_10d9cf60_Source* Source);

private:
    unsigned char unk_0[0x14];
    UnkType_10d9cf60_Notified* unk_14;
    UnkType_10d9cf60_Listener* unk_18;
};

// UnkType_10d9cf60::Unk_10d9cf60
UnkType_10d9cf60_Object* UnkType_10d9cf60::Unk_10d9cf60(UnkType_10d9cf60_Source* Source)
{
    if ( unk_18 != 0 )
    {
        unk_18->VirtualSlot3(Source);
    }
    if ( unk_14 != 0 )
    {
        unk_14->Unk_10dcdc10(Source);
    }
    if ( Source->Unk_10dcde90(0) )
    {
        Source->Unk_10dcde80();

        UnkType_10d9cf60_Object* Object =
            new(L"TransportProtocol.cpp", 0x3b) UnkType_10d9cf60_Object(Source);

        if ( Object->Unk_10d9e1b0() )
        {
            return Object;
        }
        delete Object;
    }
    return 0;
}
