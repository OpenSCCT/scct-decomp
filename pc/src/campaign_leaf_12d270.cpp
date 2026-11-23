// campaign_leaf_12d270.cpp -- method at VA 0x10a2d270: calls the method at VA 0x10a2ce10 with its
// argument, the byte at 0x9c, the value at 0xa0 and the float at 0xa4 less the float at 0xcc. The
// class, member and method names are invented; the offsets and the address are the binary's.

class UnkType_10a2d270
{
public:
    void Unk_10a2ce10(int Value, unsigned char Flag, int Other, float Delta);
    void Unk_10a2d270(int Value);

private:
    char unk_0[0x9c];
    unsigned char unk_9c;
    char unk_9d[0xa0 - 0x9d];
    int unk_a0;
    float unk_a4;
    char unk_a8[0xcc - 0xa8];
    float unk_cc;
};

// UnkType_10a2d270::Unk_10a2d270
void UnkType_10a2d270::Unk_10a2d270(int Value)
{
    Unk_10a2ce10(Value, unk_9c, unk_a0, unk_a4 - unk_cc);
}
