// campaign_leaf_766180.cpp -- thiscall method at VA 0x11066180: when the member at 0x04 is not -1,
// passes it to the cdecl function at VA 0x1104a0d0. The class, method and function names are
// invented.

void Unk_1104a0d0(int Value);

class UnkType_11066180
{
public:
    void Unk_11066180();

private:
    int unk_00;
    int unk_04;
};

// UnkType_11066180::Unk_11066180
void UnkType_11066180::Unk_11066180()
{
    if ( unk_04 != -1 )
    {
        Unk_1104a0d0(unk_04);
    }
}
