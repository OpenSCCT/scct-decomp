// campaign_leaf_4ae350.cpp -- one function at file offset 0x4ae350, preferred VA 0x10dae350.
// It passes the object to the cdecl function at 0x10d80050 and then calls the method at
// 0x10da4820 with 0. The class, function and method names are invented; the offset and the bytes
// are the binary's.

class UnkType_10dae350;

void Unk_10d80050(UnkType_10dae350* Item);

class UnkType_10dae350
{
public:
    void Unk_10da4820(int Value);
    void Unk_10dae350();
};

// UnkType_10dae350::Unk_10dae350
void UnkType_10dae350::Unk_10dae350()
{
    Unk_10d80050(this);
    Unk_10da4820(0);
}
