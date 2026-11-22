// campaign_leaf_621c70.cpp -- thiscall method at VA 0x10f21c70: passes the member at 0x0c, then the
// member at 0x00, to the stdcall function at VA 0x11039a40. All names are invented.

void __stdcall Unk_11039a40(int Value);

class UnkType_10f21c70
{
public:
    void Unk_10f21c70();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
};

// UnkType_10f21c70::Unk_10f21c70
void UnkType_10f21c70::Unk_10f21c70()
{
    Unk_11039a40(unk_0c);
    Unk_11039a40(unk_00);
}
