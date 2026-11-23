// campaign_leaf_7350c0.cpp -- one function at file offset 0x7350c0, preferred VA 0x110350c0. It
// deletes the object at 0x0 through its virtual destructor when it is set, then stores its
// argument there and zeroes the words at 0x4 and 0x8. The class, method and member names are
// invented; the offsets are the binary's.

class UnkType_110350c0_Object
{
public:
    virtual ~UnkType_110350c0_Object();
};

class UnkType_110350c0
{
public:
    void Unk_110350c0(UnkType_110350c0_Object* Object);

    UnkType_110350c0_Object* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_110350c0::Unk_110350c0
void UnkType_110350c0::Unk_110350c0(UnkType_110350c0_Object* Object)
{
    if ( unk_0 != 0 )
    {
        delete unk_0;
    }
    unk_4 = 0;
    unk_0 = Object;
    unk_8 = 0;
}
