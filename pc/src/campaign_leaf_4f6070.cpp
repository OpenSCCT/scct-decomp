// campaign_leaf_4f6070.cpp -- method at VA 0x10df6070: reads the sixteen-bit value at 0x04, the
// word at 0xb0 and the sixteen-bit value at 0x204 of its second argument from the stream that is
// its last argument (methods at VA 0x10d9dd50 and 0x10d9df90). It does not use this object. The
// class, method, member and parameter names are invented; the offsets and the addresses are the
// binary's.

class UnkType_10df6070_Reader
{
public:
    void Unk_10d9dd50(unsigned short* Value);
    void Unk_10d9df90(int* Value);
};

class UnkType_10df6070_Object
{
public:
    unsigned char unk_00[0x04];
    unsigned short unk_04;
    unsigned char unk_06[0xb0 - 0x06];
    int unk_b0;
    unsigned char unk_b4[0x204 - 0xb4];
    unsigned short unk_204;
};

class UnkType_10df6070
{
public:
    void Unk_10df6070(int Arg0, UnkType_10df6070_Object* Object, int Arg2,
                 UnkType_10df6070_Reader* Reader, int Arg4);
};

// UnkType_10df6070::Unk_10df6070
void UnkType_10df6070::Unk_10df6070(int Arg0, UnkType_10df6070_Object* Object, int Arg2,
                          UnkType_10df6070_Reader* Reader, int Arg4)
{
    Reader->Unk_10d9dd50(&Object->unk_04);
    Reader->Unk_10d9df90(&Object->unk_b0);
    Reader->Unk_10d9dd50(&Object->unk_204);
}
