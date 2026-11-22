// campaign_leaf_49be30.cpp -- thiscall at VA 0x10d9be30: returns the pointer at offset 0 when the
// boolean method at VA 0x10d7dbf0 on the same object returns true, else null. All names are
// invented.

class UnkType_10d9be30
{
public:
    bool Unk_10d7dbf0();
    void* Unk_10d9be30();

private:
    void* unk_00;
};

// UnkType_10d9be30::Unk_10d9be30
void* UnkType_10d9be30::Unk_10d9be30()
{
    if (!Unk_10d7dbf0()) {
        return 0;
    }
    return unk_00;
}
