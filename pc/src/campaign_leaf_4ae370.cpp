// campaign_leaf_4ae370.cpp -- one function at file offset 0x4ae370, preferred VA 0x10dae370.
// It passes the object to the cdecl function at 0x10d80070 and then calls the method at
// 0x10da4820 with 1. The class, function and method names are invented; the offset and the bytes
// are the binary's.

class UnkType_10dae370;

void Unk_10d80070(UnkType_10dae370* Item);

class UnkType_10dae370
{
public:
    void Unk_10da4820(int Value);
    void Unk_10dae370();
};

// UnkType_10dae370::Unk_10dae370
void UnkType_10dae370::Unk_10dae370()
{
    Unk_10d80070(this);
    Unk_10da4820(1);
}
