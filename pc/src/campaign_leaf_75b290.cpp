// campaign_leaf_75b290.cpp -- one function at file offset 0x75b290, preferred VA 0x1105b290. For
// each 8-byte entry of the array at 0x3c of the object at 0xc, counted by the word at 0xc of that
// object's table at 0x30, whose first word the function at VA 0x1104ab10 accepts, it passes both
// words to the function at VA 0x1104a8f0 and clears the second; it then sets the state at 0x4 to
// 0x15. The class, method and member names are invented; the offsets and the addresses are the
// binary's.

int Unk_1104ab10(int Kind);
void Unk_1104a8f0(int Value, int Kind);

struct UnkType_1105b290_Entry
{
    int unk_0;
    int unk_4;
};

struct UnkType_1105b290_Table
{
    unsigned char unk_0[0xc];
    int unk_c;
};

struct UnkType_1105b290_Object
{
    unsigned char unk_0[0x30];
    UnkType_1105b290_Table* unk_30;
    unsigned char unk_34[0x3c - 0x34];
    UnkType_1105b290_Entry* unk_3c;
};

class UnkType_1105b290
{
public:
    void Unk_1105b290();

    int unk_0;
    int unk_4;
    int unk_8;
    UnkType_1105b290_Object* unk_c;
};

// UnkType_1105b290::Unk_1105b290
void UnkType_1105b290::Unk_1105b290()
{
    int Index;

    for ( Index = 0; Index < unk_c->unk_30->unk_c; Index++ )
    {
        if ( Unk_1104ab10(unk_c->unk_3c[Index].unk_0) != 0 )
        {
            Unk_1104a8f0(unk_c->unk_3c[Index].unk_4, unk_c->unk_3c[Index].unk_0);
            unk_c->unk_3c[Index].unk_4 = 0;
        }
    }
    unk_4 = 0x15;
}
