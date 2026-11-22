// campaign_leaf_4a7ed0.cpp -- thiscall at VA 0x10da7ed0: returns the pointer at offset 0 when the
// boolean method at VA 0x10d88810 on the same object returns true, else null. All names are
// invented.

class UnkType_10da7ed0
{
public:
    bool Unk_10d88810();
    void* Unk_10da7ed0();

private:
    void* unk_00;
};

// UnkType_10da7ed0::Unk_10da7ed0
void* UnkType_10da7ed0::Unk_10da7ed0()
{
    if (!Unk_10d88810()) {
        return 0;
    }
    return unk_00;
}
