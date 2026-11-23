// campaign_leaf_728870.cpp -- one function at file offset 0x728870, preferred VA 0x11028870. When
// the word at 0x134 of the object at 0x6c is 4 it calls the methods at VA 0x11021080 and VA
// 0x11028490; it then clears the flag at 0x54 and returns true. The class, method and member names
// are invented; the offsets and the addresses are the binary's.

struct UnkType_11028870_Object
{
    unsigned char unk_0[0x134];
    int unk_134;
};

class UnkType_11028870
{
public:
    void Unk_11021080();
    void Unk_11028490();
    bool Unk_11028870();

    unsigned char unk_0[0x54];
    bool unk_54;
    unsigned char unk_55[0x6c - 0x55];
    UnkType_11028870_Object* unk_6c;
};

// UnkType_11028870::Unk_11028870
bool UnkType_11028870::Unk_11028870()
{
    if ( unk_6c->unk_134 == 4 )
    {
        Unk_11021080();
        Unk_11028490();
    }
    unk_54 = false;
    return true;
}
