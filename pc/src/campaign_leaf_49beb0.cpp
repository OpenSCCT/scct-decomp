// campaign_leaf_49beb0.cpp -- thiscall at VA 0x10d9beb0: returns the pointer at offset 0 of the
// member at offset 0x10 when the boolean method at VA 0x10d7dbf0 of that member returns true,
// else null. All names are invented.

struct UnkType_10d7dbf0
{
    bool Unk_10d7dbf0();

    void* unk_00;
};

class UnkType_10d9beb0
{
public:
    void* Unk_10d9beb0();

private:
    unsigned char unk_00[0x10];
    UnkType_10d7dbf0 unk_10;
};

// UnkType_10d9beb0::Unk_10d9beb0
void* UnkType_10d9beb0::Unk_10d9beb0()
{
    if (!unk_10.Unk_10d7dbf0()) {
        return 0;
    }
    return unk_10.unk_00;
}
