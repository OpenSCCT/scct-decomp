// campaign_leaf_4f4630.cpp -- method at VA 0x10df4630: calls the method at VA 0x10d9d5c0 of the
// member at 0x44 when the target is null, then again and returns when the target is that member,
// else passes both arguments to the method at VA 0x10da0990. The class, method and member names are
// invented; the offsets and the addresses are the binary's.

class UnkType_10df4630_Target
{
public:
    void Unk_10d9d5c0(int Arg);
};

class UnkType_10df4630
{
public:
    void Unk_10df4630(UnkType_10df4630_Target* Target, int Arg);
    void Unk_10da0990(UnkType_10df4630_Target* Target, int Arg);

    unsigned char unk_00[0x44];
    UnkType_10df4630_Target unk_44;
};

// UnkType_10df4630::Unk_10df4630
void UnkType_10df4630::Unk_10df4630(UnkType_10df4630_Target* Target, int Arg)
{
    if ( Target == 0 )
    {
        unk_44.Unk_10d9d5c0(Arg);
    }
    if ( Target == &unk_44 )
    {
        unk_44.Unk_10d9d5c0(Arg);
        return;
    }
    Unk_10da0990(Target, Arg);
}
