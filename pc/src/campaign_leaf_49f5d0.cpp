// campaign_leaf_49f5d0.cpp -- thiscall at VA 0x10d9f5d0: returns the pointer at offset 0 when the
// boolean method at VA 0x10d9f1d0 on the same object returns true, else null. All names are
// invented.

class UnkType_10d9f5d0
{
public:
    bool Unk_10d9f1d0();
    void* Unk_10d9f5d0();

private:
    void* unk_00;
};

// UnkType_10d9f5d0::Unk_10d9f5d0
void* UnkType_10d9f5d0::Unk_10d9f5d0()
{
    if (!Unk_10d9f1d0()) {
        return 0;
    }
    return unk_00;
}
