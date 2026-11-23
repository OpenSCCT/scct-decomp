// campaign_leaf_34d7e0.cpp -- one function at file offset 0x34d7e0, preferred VA 0x10c4d7e0. It
// passes 0 to Other's method at 0x10995870, then passes the word at 0x470 to Other's method at
// 0x10a86090 and each entry of the word array at 0x480 to the same method of the matching entry of
// Other's pointer array at 0x438 (count at 0x43c); then it calls Other's method at 0x10c4c9c0,
// stores Other at 0x46c and calls the method at 0x10c4d510 on this object and on Other. The class,
// method, member, local and parameter names are invented; the offsets and the bytes are the
// binary's.

class UnkType_10c4d7e0
{
public:
    void Unk_10995870(int Value);
    void Unk_10a86090(void* Value);
    void Unk_10c4c9c0();
    void Unk_10c4d510();
    void Unk_10c4d7e0(UnkType_10c4d7e0* Other);

    unsigned char unk_0[0x438];
    UnkType_10c4d7e0** unk_438;
    int unk_43c;
    unsigned char unk_440[0x2c];
    UnkType_10c4d7e0* unk_46c;
    void* unk_470;
    unsigned char unk_474[0xc];
    void** unk_480;
};

// UnkType_10c4d7e0::Unk_10c4d7e0
void UnkType_10c4d7e0::Unk_10c4d7e0(UnkType_10c4d7e0* Other)
{
    int Index;

    Other->Unk_10995870(0);
    Other->Unk_10a86090(unk_470);
    for ( Index = 0; Index < Other->unk_43c; Index++ )
    {
        Other->unk_438[Index]->Unk_10a86090(unk_480[Index]);
    }
    Other->Unk_10c4c9c0();
    unk_46c = Other;
    Unk_10c4d510();
    Other->Unk_10c4d510();
}
