// campaign_leaf_4ab520.cpp -- one function at file offset 0x4ab520, preferred VA 0x10dab520.
// It builds a local object with the constructor at 0x10d9ef20, passes it to the method at
// 0x10d9ea80 and destroys it with the destructor at 0x10d9d610. The class, method and variable
// names are invented; the offset and the bytes are the binary's.

class UnkType_10dab520_Local
{
public:
    unsigned char unk_0[0x30];

    UnkType_10dab520_Local();
    ~UnkType_10dab520_Local();
};

class UnkType_10dab520
{
public:
    void Unk_10d9ea80(const UnkType_10dab520_Local& Value);
    void Unk_10dab520();
};

// UnkType_10dab520::Unk_10dab520
void UnkType_10dab520::Unk_10dab520()
{
    UnkType_10dab520_Local Value;

    Unk_10d9ea80(Value);
}
