// campaign_leaf_4f5f50.cpp -- method at VA 0x10df5f50: passes its stream and index range to the
// method at VA 0x10df5d60 of its member at 0x844 and then to the method at VA 0x10df5cb0 of its
// member at 0x48. The class, method and parameter names are invented; the offsets and the addresses
// are the binary's.

class UnkType_10df5f50;

class UnkType_10df5f50_Stream;

class UnkType_10df5f50_Part48
{
public:
    void Unk_10df5cb0(UnkType_10df5f50_Stream* Stream, unsigned int First, unsigned int Last);
};

class UnkType_10df5f50_Part844
{
public:
    void Unk_10df5d60(UnkType_10df5f50_Stream* Stream, unsigned int First, unsigned int Last);
};

class UnkType_10df5f50
{
public:
    void Unk_10df5f50(UnkType_10df5f50_Stream* Stream, unsigned int First, unsigned int Last);

    unsigned char unk_00[0x48];
    UnkType_10df5f50_Part48 unk_48;
    unsigned char unk_49[0x844 - 0x49];
    UnkType_10df5f50_Part844 unk_844;
};

// UnkType_10df5f50::Unk_10df5f50
void UnkType_10df5f50::Unk_10df5f50(UnkType_10df5f50_Stream* Stream,
                                    unsigned int First, unsigned int Last)
{
    unk_844.Unk_10df5d60(Stream, First, Last);
    unk_48.Unk_10df5cb0(Stream, First, Last);
}
