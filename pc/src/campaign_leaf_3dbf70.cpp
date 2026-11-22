// campaign_leaf_3dbf70.cpp -- a member function at VA 0x10cdbf70 that passes its argument to the
// member at VA 0x10ce4280 and then the argument and the address of the member at 0x34 to the free
// function at VA 0x10cd9ed0. guess: serializes the object through an archive after its base class.
// The class, method and member names are invented; the offsets and addresses are the binary's.

class UnkType_10cd9ed0;

void Unk_10cd9ed0(UnkType_10cd9ed0& Ar, void* Value);

class UnkType_10cdbf70
{
public:
    void Unk_10ce4280(UnkType_10cd9ed0& Ar);
    void Unk_10cdbf70(UnkType_10cd9ed0& Ar);

private:
    unsigned char unk_00[0x34];
    int unk_34;
};

// UnkType_10cdbf70::Unk_10cdbf70
void UnkType_10cdbf70::Unk_10cdbf70(UnkType_10cd9ed0& Ar)
{
    Unk_10ce4280(Ar);
    Unk_10cd9ed0(Ar, &unk_34);
}
