// campaign_leaf_766180.cpp -- one function at file offset 0x766180, preferred VA 0x11066180. When
// the handle at 0x4 is not -1 it passes it to the function at VA 0x1104a0d0. The class, method and
// member names are invented; the offset and the callee's address are the binary's.

void Unk_1104a0d0(int Handle);

class UnkType_11066180
{
public:
    void Unk_11066180();

    int unk_0;
    int unk_4;
};

// UnkType_11066180::Unk_11066180
void UnkType_11066180::Unk_11066180()
{
    if ( unk_4 != -1 )
    {
        Unk_1104a0d0(unk_4);
    }
}
