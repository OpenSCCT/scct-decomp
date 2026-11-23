// campaign_leaf_75c2e0.cpp -- one function at file offset 0x75c2e0, preferred VA 0x1105c2e0. While
// the index at 0xc is below the count at 0xc of the table at 0x30 of the object at 0x8, it takes
// the next 8-byte entry of that object's array at 0x3c: when the function at VA 0x1104ab10
// rejects the entry's first word it passes both words to the function at VA 0x1104a8f0; the index
// is then advanced. Past the end it releases the array through the stdcall function at VA
// 0x1103c870, clears it, and sets the state at 0x4 to 4. The class, method and member names are
// invented; the offsets and the addresses are the binary's.

void __stdcall Unk_1103c870(void* Pointer);
int Unk_1104ab10(int Kind);
void Unk_1104a8f0(int Value, int Kind);

struct UnkType_1105c2e0_Entry
{
    int unk_0;
    int unk_4;
};

struct UnkType_1105c2e0_Table
{
    unsigned char unk_0[0xc];
    int unk_c;
};

struct UnkType_1105c2e0_Object
{
    unsigned char unk_0[0x30];
    UnkType_1105c2e0_Table* unk_30;
    unsigned char unk_34[0x3c - 0x34];
    UnkType_1105c2e0_Entry* unk_3c;
};

class UnkType_1105c2e0
{
public:
    void Unk_1105c2e0();

    int unk_0;
    int unk_4;
    UnkType_1105c2e0_Object* unk_8;
    int unk_c;
};

// UnkType_1105c2e0::Unk_1105c2e0
void UnkType_1105c2e0::Unk_1105c2e0()
{
    if ( unk_c < unk_8->unk_30->unk_c )
    {
        if ( Unk_1104ab10(unk_8->unk_3c[unk_c].unk_0) == 0 )
        {
            Unk_1104a8f0(unk_8->unk_3c[unk_c].unk_4, unk_8->unk_3c[unk_c].unk_0);
        }
        unk_c++;
        return;
    }
    if ( unk_8->unk_3c != 0 )
    {
        Unk_1103c870(unk_8->unk_3c);
        unk_8->unk_3c = 0;
    }
    unk_4 = 4;
}
