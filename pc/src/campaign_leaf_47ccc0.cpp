// campaign_leaf_47ccc0.cpp -- thiscall at VA 0x10d7ccc0: returns 0 when the pointer at offset 0
// is null, else the result of passing it to the free function at VA 0x10f32740. All names are
// invented.

int Unk_10f32740(void* Pointer);

class UnkType_10d7ccc0
{
public:
    int Unk_10d7ccc0();

private:
    void* unk_00;
};

// UnkType_10d7ccc0::Unk_10d7ccc0
int UnkType_10d7ccc0::Unk_10d7ccc0()
{
    if (!unk_00) {
        return 0;
    }
    return Unk_10f32740(unk_00);
}
