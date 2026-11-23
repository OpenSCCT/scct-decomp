// campaign_leaf_2353f0.cpp -- a member function at VA 0x10b353f0 taking an event and returning
// false: it sets the int at 0xfe0 of the object the pointer at 0x14 refers to when the object that
// object's pointer at 0x04 gives through its member at VA 0x10a0dce0 has both its pointers at 0xa8
// and 0xa4 set. It then calls its own member at VA 0x10b33610, 0x10b33db0 or 0x10b35160 for the
// first of "P_ObjectiveReview", "P_MissionStatistics" and "P_OverallAchievement" that the free
// function at VA 0x10b71bf0 accepts with the event. The class, method, member and parameter names
// are invented; the offsets, addresses and strings are the binary's.

class UnkType_10b353f0_Event;

int __cdecl Unk_10b71bf0(UnkType_10b353f0_Event* Event, const char* Name);

class UnkType_10b353f0_Info
{
public:
    unsigned char unk_000[0xa4];
    void* unk_0a4;
    void* unk_0a8;
};

class UnkType_10b353f0_Source
{
public:
    UnkType_10b353f0_Info* Unk_10a0dce0();
};

class UnkType_10b353f0_Owner
{
public:
    // guess: the info of the source, or null without one (an inline accessor; name invented)
    UnkType_10b353f0_Info* GetInfo()
    {
        return unk_004 ? unk_004->Unk_10a0dce0() : 0;
    }

    int unk_000;
    UnkType_10b353f0_Source* unk_004;
    unsigned char unk_008[0xfe0 - 0x008];
    int unk_fe0;
};

class UnkType_10b353f0
{
public:
    void Unk_10b33610();
    void Unk_10b33db0();
    void Unk_10b35160();
    bool Unk_10b353f0(UnkType_10b353f0_Event* Event);

private:
    unsigned char unk_00[0x14];
    UnkType_10b353f0_Owner* unk_14;
};

// UnkType_10b353f0::Unk_10b353f0
bool UnkType_10b353f0::Unk_10b353f0(UnkType_10b353f0_Event* Event)
{
    UnkType_10b353f0_Info* Info = unk_14->GetInfo();
    if ( Info->unk_0a8 && Info->unk_0a4 )
    {
        unk_14->unk_fe0 = 1;
    }
    if ( Unk_10b71bf0(Event, "P_ObjectiveReview") )
    {
        Unk_10b33610();
        return false;
    }
    if ( Unk_10b71bf0(Event, "P_MissionStatistics") )
    {
        Unk_10b33db0();
        return false;
    }
    if ( Unk_10b71bf0(Event, "P_OverallAchievement") )
    {
        Unk_10b35160();
    }
    return false;
}
