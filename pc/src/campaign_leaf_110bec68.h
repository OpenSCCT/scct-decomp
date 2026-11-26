#ifndef CAMPAIGN_LEAF_110BEC68_H
#define CAMPAIGN_LEAF_110BEC68_H

#include "campaign_global_111c88a0.h"

class UnkType_110bec68;

class UnkType_110bec68_Owner
{
public:
    virtual void Malloc();
    virtual void Realloc();
    virtual void Free();
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
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18(UnkType_110bec68* Object);
};

class UnkType_10966210_110bec68_Array
{
public:
    UnkType_10966210_110bec68_Array()
    : unk_00(0)
    , unk_04(0)
    , unk_08(0)
    {
        unk_00 = static_cast<unsigned char*>(GUnk_111c88a0->Realloc(unk_00, unk_08,
                                                                          L"FArray::BYTE"));
    }

    UnkType_10966210_110bec68_Array(int Count)
    : unk_00(0)
    , unk_04(Count)
    , unk_08(Count)
    {
        unk_00 = static_cast<unsigned char*>(GUnk_111c88a0->Realloc(unk_00, unk_08,
                                                                          L"FArray::BYTE"));
    }

    ~UnkType_10966210_110bec68_Array()
    {
        Unk_10966210(0, unk_04, 1);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10966210(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_110bec68_Base
{
public:
    UnkType_110bec68_Base()
    : unk_08()
    {
        unk_00 = 0;
        unk_04 = 0;
    }

    UnkType_110bec68_Base(int Count)
    : unk_08(Count)
    {
        unk_00 = 0;
        unk_04 = 0;
    }

protected:
    UnkType_110bec68_Owner* unk_00;
    int unk_04;
    UnkType_10966210_110bec68_Array unk_08;
};

class UnkType_110bec68 : public UnkType_110bec68_Base
{
public:
    UnkType_110bec68()
    : UnkType_110bec68_Base()
    {
    }

    UnkType_110bec68(int Count)
    : UnkType_110bec68_Base(Count)
    {
    }

    virtual ~UnkType_110bec68()
    {
        if ( unk_00 )
        {
            unk_00->VirtualSlot18(this);
        }
    }
};

#endif
