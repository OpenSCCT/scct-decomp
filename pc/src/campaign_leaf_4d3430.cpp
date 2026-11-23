// campaign_leaf_4d3430.cpp -- one function at file offset 0x4d3430, preferred VA 0x10dd3430.
// It calls the method at 0x10d84fd0 with Flags when every bit of Flags is set in the int at offset
// 0x10 of the object the function at 0x10d97fe0 returns. The class, function, method, member and
// parameter names are invented; the offset and the bytes are the binary's.

struct UnkType_10dd3430_Settings
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
};

UnkType_10dd3430_Settings* Unk_10d97fe0();

class UnkType_10dd3430
{
public:
    void Unk_10d84fd0(int Flags);
    void Unk_10dd3430(int Flags);
};

// UnkType_10dd3430::Unk_10dd3430
void UnkType_10dd3430::Unk_10dd3430(int Flags)
{
    if ( (Unk_10d97fe0()->unk_10 & Flags) == Flags )
    {
        Unk_10d84fd0(Flags);
    }
}
