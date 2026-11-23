// campaign_leaf_763820.cpp -- one function at file offset 0x763820, preferred VA 0x11063820. It
// returns 0 when the member at 0x70 is clear and the function at VA 0x1106e370 fails to fill it
// from the block at 0x4c, the record's word at 0x8 and the word at 0x20 of the object at 0x4, or
// when the member at 0x88 is clear, the word at 0x48 is set and the function at VA 0x1106de70
// fails to fill it from the block at 0x4c; it returns 1 otherwise. The class, method and member
// names are invented; the offsets and the addresses are the binary's.

struct UnkType_11063820_Record
{
    int unk_0;
    int unk_4;
    int unk_8;
};

struct UnkType_11063820_Owner
{
    unsigned char unk_0[0x20];
    int unk_20;
};

int Unk_1106e370(void** Object, void* Block, int Value, int Extra);
int Unk_1106de70(void** Object, void* Block);

class UnkType_11063820
{
public:
    int Unk_11063820(UnkType_11063820_Record* Record);

    int unk_0;
    UnkType_11063820_Owner* unk_4;
    unsigned char unk_8[0x48 - 0x8];
    int unk_48;
    unsigned char unk_4c[0x70 - 0x4c];
    void* unk_70;
    unsigned char unk_74[0x88 - 0x74];
    void* unk_88;
};

// UnkType_11063820::Unk_11063820
int UnkType_11063820::Unk_11063820(UnkType_11063820_Record* Record)
{
    if ( unk_70 == 0 && Unk_1106e370(&unk_70, unk_4c, Record->unk_8, unk_4->unk_20) != 0 )
    {
        return 0;
    }
    if ( unk_88 == 0 && unk_48 != 0 && Unk_1106de70(&unk_88, unk_4c) != 0 )
    {
        return 0;
    }
    return 1;
}
