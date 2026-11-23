// campaign_leaf_766940.cpp -- one function at file offset 0x766940, preferred VA 0x11066940. The
// first object it is given is stored at 0x10 when that member is clear. Otherwise the object at
// 0x18 that is set is passed to the method at VA 0x110666a0 of the member at 0x20, the new object
// is stored at 0x18, and when the first item (method at VA 0x11067220) of the object at 0x10 has
// the kind 3 at 0x28 the method at VA 0x110664b0 runs. Either way the stored object then takes
// the word at 0xd8 of the record through its method at VA 0x110671f0. The class, method and
// member names are invented; the offsets and the addresses are the binary's.

struct UnkType_11066940_Item
{
    unsigned char unk_0[0x28];
    int unk_28;
};

class UnkType_11066940_Iterator
{
public:
    UnkType_11066940_Iterator();

    UnkType_11066940_Item* unk_0;
};

class UnkType_11066940_Object
{
public:
    void Unk_110671f0(int Value);
    UnkType_11066940_Iterator Unk_11067220();
};

class UnkType_11066940_List
{
public:
    void Unk_110666a0(UnkType_11066940_Object* Object);
};

struct UnkType_11066940_Record
{
    unsigned char unk_0[0xd8];
    int unk_d8;
};

class UnkType_11066940
{
public:
    void Unk_110664b0();
    void Unk_11066940(UnkType_11066940_Object* Object, UnkType_11066940_Record* Record);

    unsigned char unk_0[0x10];
    UnkType_11066940_Object* unk_10;
    unsigned char unk_14[0x18 - 0x14];
    UnkType_11066940_Object* unk_18;
    unsigned char unk_1c[0x20 - 0x1c];
    UnkType_11066940_List unk_20;
};

// UnkType_11066940::Unk_11066940
void UnkType_11066940::Unk_11066940(UnkType_11066940_Object* Object,
                                    UnkType_11066940_Record* Record)
{
    if ( unk_10 == 0 )
    {
        unk_10 = Object;
        Object->Unk_110671f0(Record->unk_d8);
        return;
    }
    if ( unk_18 != 0 )
    {
        unk_20.Unk_110666a0(unk_18);
    }
    unk_18 = Object;
    if ( unk_10->Unk_11067220().unk_0->unk_28 == 3 )
    {
        Unk_110664b0();
    }
    unk_18->Unk_110671f0(Record->unk_d8);
}
