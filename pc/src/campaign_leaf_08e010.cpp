// campaign_leaf_08e010.cpp -- method at VA 0x1098e010: returns 0 when the object its first argument
// points to exists, has bit 15 of its value at 0x2c set and its value at 0x6c equal to the value at
// 0x2b4 of this object, or when bit 3 of the second argument is set; otherwise returns what the
// method at VA 0x1098dd60 returns for the three arguments. The class, member and method names are
// invented; the offsets, the bits and the address are the binary's.

class UnkType_1098e010_Object
{
public:
    unsigned char unk_00[0x2c];
    unsigned int unk_2c;
    unsigned char unk_30[0x6c - 0x30];
    int unk_6c;
};

class UnkType_1098e010
{
public:
    int Unk_1098e010(UnkType_1098e010_Object* Object, unsigned int Flags, int Value);
    int Unk_1098dd60(UnkType_1098e010_Object* Object, unsigned int Flags, int Value);

private:
    unsigned char unk_000[0x2b4];
    int unk_2b4;
};

// UnkType_1098e010::Unk_1098e010
int UnkType_1098e010::Unk_1098e010(UnkType_1098e010_Object* Object, unsigned int Flags,
                                   int Value)
{
    if ( (Object && (Object->unk_2c & 0x8000) && Object->unk_6c == unk_2b4) || (Flags & 8) )
    {
        return 0;
    }
    return Unk_1098dd60(Object, Flags, Value);
}
