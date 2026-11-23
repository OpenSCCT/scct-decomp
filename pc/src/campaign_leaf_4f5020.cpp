// campaign_leaf_4f5020.cpp -- method at VA 0x10df5020: reads the word at 0x00 (method at VA
// 0x10d9df90) and the sixteen-bit value at 0x04 (method at VA 0x10d9dd50) of its second argument
// from the stream that is its fourth argument. It does not use this object. The class, method,
// member and parameter names are invented; the offsets and the addresses are the binary's.

class UnkType_10df5020_Reader
{
public:
    void Unk_10d9dd50(unsigned short* Value);
    void Unk_10d9df90(int* Value);
};

class UnkType_10df5020_Object
{
public:
    int unk_00;
    unsigned short unk_04;
};

class UnkType_10df5020
{
public:
    void Unk_10df5020(int Arg0, UnkType_10df5020_Object* Object, int Arg2,
                 UnkType_10df5020_Reader* Reader, int Arg4);
};

// UnkType_10df5020::Unk_10df5020
void UnkType_10df5020::Unk_10df5020(int Arg0, UnkType_10df5020_Object* Object, int Arg2,
                          UnkType_10df5020_Reader* Reader, int Arg4)
{
    Reader->Unk_10d9df90(&Object->unk_00);
    Reader->Unk_10d9dd50(&Object->unk_04);
}
