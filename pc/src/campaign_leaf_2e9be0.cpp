// campaign_leaf_2e9be0.cpp -- method at VA 0x10be9be0 taking 12 bytes by value and three words: when
// the byte at 0x4c is 2 and bit 16 of the word at 0x2c is set, clears bit 31 of the word at 0x28;
// then passes all its arguments on to the method at VA 0x10a92550. The class, member and method
// names are invented; the offsets and the address are the binary's.

class UnkType_10be9be0_Vector
{
public:
    float unk_00;
    float unk_04;
    float unk_08;
};

class UnkType_10be9be0
{
public:
    void Unk_10be9be0(UnkType_10be9be0_Vector Location, int First, int Second, int Third);
    void Unk_10a92550(UnkType_10be9be0_Vector Location, int First, int Second, int Third);

private:
    unsigned char unk_00[0x28];
    unsigned int unk_28;
    unsigned char unk_2c[0x2e - 0x2c];
    unsigned char unk_2e;
    unsigned char unk_2f[0x4c - 0x2f];
    unsigned char unk_4c;
};

// UnkType_10be9be0::Unk_10be9be0
void UnkType_10be9be0::Unk_10be9be0(UnkType_10be9be0_Vector Location, int First, int Second,
                                    int Third)
{
    if ( unk_4c != 2 )
    {
        Unk_10a92550(Location, First, Second, Third);
        return;
    }
    if ( unk_2e & 1 )
    {
        unk_28 &= 0x7fffffff;
    }
    Unk_10a92550(Location, First, Second, Third);
}
