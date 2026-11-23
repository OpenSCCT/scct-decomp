// campaign_leaf_766170.cpp -- thiscall method at VA 0x11066170: when the member at 0x04 is not -1,
// passes it to the cdecl function at VA 0x1104a100. The class, method and function names are
// invented.

void Unk_1104a100(int Value);

class UnkType_11066170
{
public:
    void Unk_11066170();

private:
    int unk_00;
    int unk_04;
};

// UnkType_11066170::Unk_11066170
void UnkType_11066170::Unk_11066170()
{
    if ( unk_04 != -1 )
    {
        Unk_1104a100(unk_04);
    }
}
