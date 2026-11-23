// campaign_leaf_4f47c0.cpp -- stdcall function at VA 0x10df47c0: for the object it is given, calls
// the method at VA 0x10d9d5c0 of the object's member at 0x44 when the target is null, then again
// and returns when the target is that member, else passes the target and the last argument to the
// object's method at VA 0x10da0990. The class, function and member names are invented; the offsets
// and the addresses are the binary's.

class UnkType_10df47c0_Target
{
public:
    void Unk_10d9d5c0(int Arg);
};

class UnkType_10df47c0
{
public:
    void Unk_10da0990(UnkType_10df47c0_Target* Target, int Arg);

    unsigned char unk_00[0x44];
    UnkType_10df47c0_Target unk_44;
};

// Unk_10df47c0
void __stdcall Unk_10df47c0(UnkType_10df47c0* Object, UnkType_10df47c0_Target* Target, int Arg)
{
    if ( Target == 0 )
    {
        Object->unk_44.Unk_10d9d5c0(Arg);
    }
    if ( Target == &Object->unk_44 )
    {
        Object->unk_44.Unk_10d9d5c0(Arg);
        return;
    }
    Object->Unk_10da0990(Target, Arg);
}
