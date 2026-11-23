// campaign_leaf_266f10.cpp -- a member function at VA 0x10b66f10 taking a flag: it returns false
// unless the object the pointer at 0x34 refers to exists and the item pointer at 0x08 of its part
// at 0x14 is set. When the flag is set and bit 0 of the item's flag byte at 0x20 is clear, it calls
// the item's member at VA 0x10d30870 with 1; when the flag is clear and that bit is set, it calls
// the item's members at VA 0x10d30870 with 0 and VA 0x10d308c0 with 0 and 0. It then returns true.
// The class, method, member and parameter names are invented; the offsets and addresses are the
// binary's.

class UnkType_10b66f10_Item
{
public:
    void Unk_10d30870(int Value);
    void Unk_10d308c0(int First, int Second);

    unsigned char unk_00[0x20];
    unsigned char unk_20;
};

class UnkType_10b66f10_Part
{
public:
    int unk_00;
    int unk_04;
    UnkType_10b66f10_Item* unk_08;
};

class UnkType_10b66f10_Owner
{
public:
    // guess: the part at 0x14 (an inline accessor; name invented)
    UnkType_10b66f10_Part* GetPart()
    {
        return &unk_14;
    }

    unsigned char unk_00[0x14];
    UnkType_10b66f10_Part unk_14;
};

class UnkType_10b66f10
{
public:
    bool Unk_10b66f10(bool Flag);

private:
    unsigned char unk_00[0x34];
    UnkType_10b66f10_Owner* unk_34;
};

// UnkType_10b66f10::Unk_10b66f10
bool UnkType_10b66f10::Unk_10b66f10(bool Flag)
{
    if ( !unk_34 || !unk_34->GetPart() || !unk_34->GetPart()->unk_08 )
    {
        return false;
    }
    if ( Flag )
    {
        if ( !( unk_34->GetPart()->unk_08->unk_20 & 1 ) )
        {
            unk_34->GetPart()->unk_08->Unk_10d30870(1);
        }
    }
    else if ( unk_34->GetPart()->unk_08->unk_20 & 1 )
    {
        unk_34->GetPart()->unk_08->Unk_10d30870(0);
        unk_34->GetPart()->unk_08->Unk_10d308c0(0, 0);
    }
    return true;
}
