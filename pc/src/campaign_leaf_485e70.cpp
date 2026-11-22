// campaign_leaf_485e70.cpp -- thiscall at VA 0x10d85e70: calls the method at VA 0x10d85750 on the
// same object with the address of the member at offset 0x18 and its two arguments. All names are
// invented.

class UnkType_10d85e70
{
public:
    void Unk_10d85750(void* Member, int First, int Second);
    void Unk_10d85e70(int First, int Second);

private:
    unsigned char unk_00[0x18];
    int unk_18;
};

// UnkType_10d85e70::Unk_10d85e70
void UnkType_10d85e70::Unk_10d85e70(int First, int Second)
{
    Unk_10d85750(&unk_18, First, Second);
}
