// campaign_leaf_718c30.cpp -- one function at file offset 0x718c30, preferred VA 0x11018c30. For
// each of the objects at 0x18 and 0x1c that is set it increments the object's short at 0x6 and
// passes this object to its method at VA 0x10e50290. The class, method and member names are
// invented; the offsets and the callee's address are the binary's.

class UnkType_11018c30;

class UnkType_11018c30_Object
{
public:
    void Unk_10e50290(UnkType_11018c30* Owner);

    int unk_0;
    short unk_4;
    short unk_6;
};

class UnkType_11018c30
{
public:
    void Unk_11018c30();

    unsigned char unk_0[0x18];
    UnkType_11018c30_Object* unk_18;
    UnkType_11018c30_Object* unk_1c;
};

// UnkType_11018c30::Unk_11018c30
void UnkType_11018c30::Unk_11018c30()
{
    if ( unk_18 != 0 )
    {
        ++unk_18->unk_6;
        unk_18->Unk_10e50290(this);
    }
    if ( unk_1c != 0 )
    {
        ++unk_1c->unk_6;
        unk_1c->Unk_10e50290(this);
    }
}
