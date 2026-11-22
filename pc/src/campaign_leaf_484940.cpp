// campaign_leaf_484940.cpp -- thiscall at VA 0x10d84940: returns the pointer at offset 0 when the
// boolean method at VA 0x10d845f0 on the same object returns true, else null. All names are
// invented.

class UnkType_10d84940
{
public:
    bool Unk_10d845f0();
    void* Unk_10d84940();

private:
    void* unk_00;
};

// UnkType_10d84940::Unk_10d84940
void* UnkType_10d84940::Unk_10d84940()
{
    if (!Unk_10d845f0()) {
        return 0;
    }
    return unk_00;
}
