// campaign_leaf_766170.cpp -- one function at file offset 0x766170, preferred VA 0x11066170. When
// the handle at 0x4 is not -1 it passes it to the function at VA 0x1104a100. The class, method and
// member names are invented; the offset and the callee's address are the binary's.

void Unk_1104a100(int Handle);

class UnkType_11066170
{
public:
    void Unk_11066170();

    int unk_0;
    int unk_4;
};

// UnkType_11066170::Unk_11066170
void UnkType_11066170::Unk_11066170()
{
    if ( unk_4 != -1 )
    {
        Unk_1104a100(unk_4);
    }
}
