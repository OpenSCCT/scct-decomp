// campaign_leaf_337050.cpp -- one function at file offset 0x337050, preferred VA 0x10c37050. When
// the word at 0x84 is set and the mutex at 0x88 is free within a millisecond, it passes the value
// the method at 0x10c37d90 returns for the member at 0x78 to virtual slot 9, keeps its result
// and releases the mutex; in every case it stores the word at 0x74 through Out and returns the
// kept result, or 0. The class, method, member, local and parameter names are invented; the
// imports are named by the retail import table, and the slot, offsets and bytes are the binary's.

#include "campaign_import_ReleaseMutex.h"
#include "campaign_import_WaitForSingleObject.h"

class UnkType_10c37d90
{
public:
    UnkType_10c37d90();

    int unk_0;
    int unk_4;
};

class UnkType_10c37050_Queue
{
public:
    UnkType_10c37d90 Unk_10c37d90();
};

class UnkType_10c37050
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
    virtual int VirtualSlot9(UnkType_10c37d90 Value);
    int Unk_10c37050(int* Out);

    unsigned char unk_4[0x70];
    int unk_74;
    UnkType_10c37050_Queue unk_78;
    unsigned char unk_79[0xb];
    int unk_84;
    HANDLE unk_88;
};

// UnkType_10c37050::Unk_10c37050
int UnkType_10c37050::Unk_10c37050(int* Out)
{
    int Result = 0;

    if ( unk_84 != 0 && WaitForSingleObject(unk_88, 1) == WAIT_OBJECT_0 )
    {
        UnkType_10c37d90 Value = unk_78.Unk_10c37d90();
        Result = VirtualSlot9(Value);
        ReleaseMutex(unk_88);
    }
    *Out = unk_74;
    return Result;
}
