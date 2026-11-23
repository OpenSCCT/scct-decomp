// campaign_leaf_567300.cpp -- thiscall method at VA 0x10e67300: builds a message from the 16-bit
// value it is given, the object and its two members at 0x0c and 0x10, passes it with the member at
// 0x08 to the cdecl function at VA 0x10e66ae0, then to the function at VA 0x10e63820 for each of
// the two members whose word at 0x64 is set. All names are invented.

class UnkType_10e67300;

struct UnkType_10e67300_Party
{
    int unk_00[25];
    int unk_64;
};

struct UnkType_10e67300_Message
{
    short unk_00;
    UnkType_10e67300* unk_04;
    UnkType_10e67300_Party* unk_08;
    UnkType_10e67300_Party* unk_0c;
    int unk_10;
};

void Unk_10e66ae0(int Target, UnkType_10e67300_Message* Message);
void Unk_10e63820(UnkType_10e67300_Party* Party, UnkType_10e67300_Message* Message);

class UnkType_10e67300
{
public:
    void Unk_10e67300(short Value);

private:
    int unk_00;
    int unk_04;
    int unk_08;
    UnkType_10e67300_Party* unk_0c;
    UnkType_10e67300_Party* unk_10;
};

// UnkType_10e67300::Unk_10e67300
void UnkType_10e67300::Unk_10e67300(short Value)
{
    UnkType_10e67300_Party* First = unk_0c;
    UnkType_10e67300_Party* Second = unk_10;
    UnkType_10e67300_Message Message;
    Message.unk_00 = Value;
    Message.unk_04 = this;
    Message.unk_08 = First;
    Message.unk_0c = Second;
    Unk_10e66ae0(unk_08, &Message);
    if ( First->unk_64 )
    {
        Unk_10e63820(First, &Message);
    }
    if ( Second->unk_64 )
    {
        Unk_10e63820(Second, &Message);
    }
}
