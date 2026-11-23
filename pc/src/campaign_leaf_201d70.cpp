// campaign_leaf_201d70.cpp -- thiscall method at VA 0x10b01d70. Given a pointer to a key, it finds
// the slot (key modulo 40) in the table of 40 slots at 0x4a8, each a flag byte and a 0x18-byte
// object; when the slot's flag is set it sets the flag, destroys the object (destructor at VA
// 0x10afeef0), clears the flag of the slot the key now selects and returns true; otherwise it
// returns false. The class, method and member names are invented.

class UnkType_10afeef0
{
public:
    ~UnkType_10afeef0();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
};

struct UnkType_10afeef0_Slot
{
    bool bUsed;
    UnkType_10afeef0 Value;
};

class UnkType_10b01d70
{
public:
    bool Unk_10b01d70(const unsigned int* Key);

private:
    char unk_000[0x4a8];
    UnkType_10afeef0_Slot unk_4a8[40];
};

// UnkType_10b01d70::Unk_10b01d70
bool UnkType_10b01d70::Unk_10b01d70(const unsigned int* Key)
{
    UnkType_10afeef0_Slot& Slot = unk_4a8[*Key % 40];
    if ( Slot.bUsed )
    {
        Slot.bUsed = true;
        Slot.Value.~UnkType_10afeef0();
        unk_4a8[*Key % 40].bUsed = false;
        return true;
    }
    return false;
}
