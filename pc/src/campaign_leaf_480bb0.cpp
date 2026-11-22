// campaign_leaf_480bb0.cpp -- thiscall at VA 0x10d80bb0: returns the pointer at offset 0 when the
// boolean method at VA 0x10d80480 on the same object returns true, else null. All names are
// invented.

class UnkType_10d80bb0
{
public:
    bool Unk_10d80480();
    void* Unk_10d80bb0();

private:
    void* unk_00;
};

// UnkType_10d80bb0::Unk_10d80bb0
void* UnkType_10d80bb0::Unk_10d80bb0()
{
    if (!Unk_10d80480()) {
        return 0;
    }
    return unk_00;
}
