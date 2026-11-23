// campaign_leaf_4fbb40.cpp -- method at VA 0x10dfbb40: reads the time in seconds from the timer
// the free function at VA 0x10dfbc20 returns (QueryPerformanceCounter times its seconds per count
// at 0x8); calls the method at VA 0x10dfba00 when the value at 0x18 is set; calls virtual slot 5
// (vtable offset 0x14) with Value; stores the seconds that took at 0x4 and returns the slot's
// result. The class, member, method and parameter names are invented; the import is named by the
// retail import table, and the offsets, the slot and the addresses are the binary's.

#include "campaign_import_QueryPerformanceCounter.h"

#pragma pack(push, 4)

class UnkType_10dfbb40_Timer
{
public:
    double Seconds()
    {
        LARGE_INTEGER Count;

        QueryPerformanceCounter(&Count);
        return Count.QuadPart * unk_8;
    }

private:
    LARGE_INTEGER unk_0;
    double unk_8;
};

UnkType_10dfbb40_Timer* Unk_10dfbc20();

class UnkType_10dfbb40
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual int VirtualSlot5(int Value);

    void Unk_10dfba00();
    int Unk_10dfbb40(int Value);

private:
    double unk_4;
    char unk_c[0x18 - 0xc];
    int unk_18;
};

#pragma pack(pop)

// UnkType_10dfbb40::Unk_10dfbb40
int UnkType_10dfbb40::Unk_10dfbb40(int Value)
{
    double Start = Unk_10dfbc20()->Seconds();
    int Result;

    if ( unk_18 )
    {
        Unk_10dfba00();
    }
    Result = VirtualSlot5(Value);
    unk_4 = Unk_10dfbc20()->Seconds() - Start;
    return Result;
}
