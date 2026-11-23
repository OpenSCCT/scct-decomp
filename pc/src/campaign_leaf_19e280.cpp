// campaign_leaf_19e280.cpp -- one function at file offset 0x19e280, preferred VA 0x10a9e280.
// It passes each of the six 0x154-byte members at offsets 0x4, 0x158, 0x2ac, 0x400, 0x554 and
// 0x6a8 to its argument's method at VA 0x10d9e050.
// The class, method and member names are invented; the offset and the bytes are the binary's.

struct UnkType_10a9e280_Element
{
    unsigned char unk_0[0x154];
};

class UnkType_10a9e280_Reader
{
public:
    void Unk_10d9e050(UnkType_10a9e280_Element* Element);
};

class UnkType_10a9e280
{
public:
    unsigned char unk_0[0x4];
    UnkType_10a9e280_Element unk_4;
    UnkType_10a9e280_Element unk_158;
    UnkType_10a9e280_Element unk_2ac;
    UnkType_10a9e280_Element unk_400;
    UnkType_10a9e280_Element unk_554;
    UnkType_10a9e280_Element unk_6a8;

    void Unk_10a9e280(UnkType_10a9e280_Reader* Reader);
};

// UnkType_10a9e280::Unk_10a9e280
void UnkType_10a9e280::Unk_10a9e280(UnkType_10a9e280_Reader* Reader)
{
    Reader->Unk_10d9e050(&unk_4);
    Reader->Unk_10d9e050(&unk_158);
    Reader->Unk_10d9e050(&unk_2ac);
    Reader->Unk_10d9e050(&unk_400);
    Reader->Unk_10d9e050(&unk_554);
    Reader->Unk_10d9e050(&unk_6a8);
}
