// campaign_leaf_484d40.cpp -- thiscall method at VA 0x10d84d40. Its log message names it
// SetMasterStation. Unless the given 8-bit number is higher than its own at 0x14 (counting
// modulo 256), it calls its twelfth virtual method with 1 and logs, at level 4, "Incorrect call
// to SetMasterStation: %d (%x) is not higher than %d (%x)" with both numbers and keys. It then
// assigns its reference at 0x8 one built from the given key (constructor at 0x10d8ef70,
// assignment at 0x10d8ef20, destructor at 0x10d8edb0) and keeps the number at 0x14. The class,
// method and parameter names are invented.

extern "C" int __cdecl abs(int Value);

void Unk_10d97ba0(int Level, const unsigned short* Format, ...);

// guess: the inline that tells how far the current 8-bit number is ahead of the given one,
// counting modulo 256
inline int NumberDifference(int Number, int Current)
{
    int Difference = Current - Number;

    if ( abs(Difference) < 0x80 )
    {
        return Difference;
    }
    if ( Current < Number )
    {
        return Difference + 0x100;
    }
    return Difference - 0x100;
}

struct UnkType_10d84d40_Key
{
    UnkType_10d84d40_Key(const UnkType_10d84d40_Key& Other) : unk_0(Other.unk_0) {}

    int unk_0;
};

class UnkType_10d84d40_Ref
{
public:
    UnkType_10d84d40_Ref(UnkType_10d84d40_Key Key);
    ~UnkType_10d84d40_Ref();
    UnkType_10d84d40_Ref& operator=(const UnkType_10d84d40_Ref& Other);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10d84d40
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
    virtual void VirtualSlot11(int Value);

    void Unk_10d84d40(UnkType_10d84d40_Key Station, unsigned char Number);

private:
    int unk_4;
    UnkType_10d84d40_Ref unk_8;
    unsigned char unk_14;
};

// UnkType_10d84d40::Unk_10d84d40
void UnkType_10d84d40::Unk_10d84d40(UnkType_10d84d40_Key Station, unsigned char Number)
{
    if ( unk_14 == Number || NumberDifference(Number, unk_14) > 0 )
    {
        VirtualSlot11(1);
        Unk_10d97ba0(4, L"Incorrect call to SetMasterStation: %d (%x) is not higher than %d (%x)",
                     Number, Station.unk_0, unk_14, unk_8.unk_4);
    }
    unk_8 = Station;
    unk_14 = Number;
}
