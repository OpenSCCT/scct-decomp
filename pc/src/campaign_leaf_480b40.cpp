// campaign_leaf_480b40.cpp -- thiscall at VA 0x10d80b40: returns the pointer at offset 0 when the
// boolean method at VA 0x10d801e0 on the same object returns true, else null. All names are
// invented.

class UnkType_10d80b40
{
public:
    bool Unk_10d801e0();
    void* Unk_10d80b40();

private:
    void* unk_00;
};

// UnkType_10d80b40::Unk_10d80b40
void* UnkType_10d80b40::Unk_10d80b40()
{
    if (!Unk_10d801e0()) {
        return 0;
    }
    return unk_00;
}
