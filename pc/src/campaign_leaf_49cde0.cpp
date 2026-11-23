// campaign_leaf_49cde0.cpp -- thiscall method at VA 0x10d9cde0, from TransportProtocol.cpp (the
// wide file name and line 82 it passes to the allocating operator new). It creates a 0x14-byte
// object with 0x400 (constructor at 0x10dcdff0), hands it the value the given object's method at
// 0x10d9d680 returns (0x10dce1e0) and 0 (0x10dce260), passes it to the method at 0x10dcdab0 of the
// object at 0x14 and to the second virtual method of the object at 0x18 when they exist, and
// returns it. The class, method and parameter names are invented.

void* operator new(unsigned int Size, const unsigned short* File, int Line);

class UnkType_10d9cde0_Source
{
public:
    int Unk_10d9d680();
};

class UnkType_10d9cde0_Buffer
{
public:
    UnkType_10d9cde0_Buffer(int Size);
    void Unk_10dce1e0(int Value);
    void Unk_10dce260(int Value);

private:
    unsigned char unk_0[0x14];
};

class UnkType_10d9cde0_First
{
public:
    void Unk_10dcdab0(UnkType_10d9cde0_Buffer* Buffer);
};

class UnkType_10d9cde0_Second
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(UnkType_10d9cde0_Buffer* Buffer);
};

class UnkType_10d9cde0
{
public:
    UnkType_10d9cde0_Buffer* Unk_10d9cde0(UnkType_10d9cde0_Source* Source);

private:
    unsigned char unk_0[0x14];
    UnkType_10d9cde0_First* unk_14;
    UnkType_10d9cde0_Second* unk_18;
};

// UnkType_10d9cde0::Unk_10d9cde0
UnkType_10d9cde0_Buffer* UnkType_10d9cde0::Unk_10d9cde0(UnkType_10d9cde0_Source* Source)
{
    UnkType_10d9cde0_Buffer* Buffer;

    Buffer = new(L"TransportProtocol.cpp", 0x52) UnkType_10d9cde0_Buffer(0x400);
    Buffer->Unk_10dce1e0(Source->Unk_10d9d680());
    Buffer->Unk_10dce260(0);
    if ( unk_14 )
    {
        unk_14->Unk_10dcdab0(Buffer);
    }
    if ( unk_18 )
    {
        unk_18->VirtualSlot1(Buffer);
    }
    return Buffer;
}
