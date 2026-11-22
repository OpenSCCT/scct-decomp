// campaign_leaf_480b20.cpp -- thiscall at VA 0x10d80b20: returns the pointer at offset 0 when the
// boolean method at VA 0x10d801e0 on the same object returns true, else null. All names are
// invented.

class UnkType_10d80b20
{
public:
    bool Unk_10d801e0();
    void* Unk_10d80b20();

private:
    void* unk_00;
};

// UnkType_10d80b20::Unk_10d80b20
void* UnkType_10d80b20::Unk_10d80b20()
{
    if (!Unk_10d801e0()) {
        return 0;
    }
    return unk_00;
}
