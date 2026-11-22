// campaign_leaf_2d6190.cpp -- a member function at VA 0x10bd6190 that stores its byte argument at
// 0x330 and then calls the member at VA 0x10bd60d0. The class, method and member names are
// invented; the offsets and addresses are the binary's.

class UnkType_10bd6190
{
public:
    void Unk_10bd60d0();
    void Unk_10bd6190(unsigned char Value);

private:
    unsigned char unk_000[0x330];
    unsigned char unk_330;
};

// UnkType_10bd6190::Unk_10bd6190
void UnkType_10bd6190::Unk_10bd6190(unsigned char Value)
{
    unk_330 = Value;
    Unk_10bd60d0();
}
