// campaign_leaf_484920.cpp -- thiscall at VA 0x10d84920: returns the pointer at offset 0 when the
// boolean method at VA 0x10d7dbf0 on the same object returns true, else null. All names are
// invented.

class UnkType_10d84920
{
public:
    bool Unk_10d7dbf0();
    void* Unk_10d84920();

private:
    void* unk_00;
};

// UnkType_10d84920::Unk_10d84920
void* UnkType_10d84920::Unk_10d84920()
{
    if (!Unk_10d7dbf0()) {
        return 0;
    }
    return unk_00;
}
