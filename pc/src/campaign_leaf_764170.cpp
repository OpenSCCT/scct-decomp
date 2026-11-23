// campaign_leaf_764170.cpp -- one function at file offset 0x764170, preferred VA 0x11064170. When
// the record at 0x4 is set and its first word equals the argument, it calls the method at VA
// 0x1106d330 on the object at 0x78 and the method at VA 0x1106de60 on the object at 0x88, each
// only when its pointer is set. The class, method and member names are invented; the offsets and
// the addresses are the binary's.

class UnkType_11064170_First
{
public:
    void Unk_1106d330();
};

class UnkType_11064170_Second
{
public:
    void Unk_1106de60();
};

class UnkType_11064170
{
public:
    void Unk_11064170(int Value);

    int unk_0;
    int* unk_4;
    unsigned char unk_8[0x78 - 0x8];
    UnkType_11064170_First* unk_78;
    unsigned char unk_7c[0x88 - 0x7c];
    UnkType_11064170_Second* unk_88;
};

// UnkType_11064170::Unk_11064170
void UnkType_11064170::Unk_11064170(int Value)
{
    if ( unk_4 != 0 && *unk_4 == Value )
    {
        if ( unk_78 != 0 )
        {
            unk_78->Unk_1106d330();
        }
        if ( unk_88 != 0 )
        {
            unk_88->Unk_1106de60();
        }
    }
}
