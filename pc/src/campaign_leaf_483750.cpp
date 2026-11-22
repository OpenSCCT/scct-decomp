// campaign_leaf_483750.cpp -- thiscall at VA 0x10d83750: calls the method at VA 0x10d8ee40 on the
// same object when the pointer at offset 0 is null, then returns whether it is set. All names are
// invented.

class UnkType_10d83750
{
public:
    void Unk_10d8ee40();
    int Unk_10d83750();

private:
    void* unk_00;
};

// UnkType_10d83750::Unk_10d83750
int UnkType_10d83750::Unk_10d83750()
{
    if (!unk_00) {
        Unk_10d8ee40();
    }
    return unk_00 != 0;
}
