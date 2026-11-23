// campaign_leaf_378630.cpp -- one function at file offset 0x378630, preferred VA 0x10c78630. It
// serializes this object through Ar: the method at 0x10a4b4f0 first; then, unless Ar's words at
// 0x1c or 0x18 are set, the member at 0x220 with the function at 0x10a56210, the word at 0x22c
// through the returned archive's virtual slot 1 and the member at 0x230 with the function at
// 0x10aa73c0. The class, method, member and parameter names are invented; the offsets, the slot
// and the bytes are the binary's.

class UnkType_10c78630_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Size);

    unsigned char unk_4[0x14];
    int unk_18;
    int unk_1c;
};

struct UnkType_10c78630_First
{
    unsigned char unk_0[0xc];
};

struct UnkType_10c78630_Second
{
    unsigned char unk_0[0x4];
};

UnkType_10c78630_Archive& Unk_10a56210(UnkType_10c78630_Archive& Ar,
                                       UnkType_10c78630_First& Value);
UnkType_10c78630_Archive& Unk_10aa73c0(UnkType_10c78630_Archive& Ar,
                                       UnkType_10c78630_Second& Value);

class UnkType_10c78630
{
public:
    void Unk_10a4b4f0(UnkType_10c78630_Archive& Ar);
    void Unk_10c78630(UnkType_10c78630_Archive& Ar);

    unsigned char unk_0[0x220];
    UnkType_10c78630_First unk_220;
    int unk_22c;
    UnkType_10c78630_Second unk_230;
};

// UnkType_10c78630::Unk_10c78630
void UnkType_10c78630::Unk_10c78630(UnkType_10c78630_Archive& Ar)
{
    Unk_10a4b4f0(Ar);
    if ( Ar.unk_1c == 0 && Ar.unk_18 == 0 )
    {
        UnkType_10c78630_Archive& Out = Unk_10a56210(Ar, unk_220);

        Out.VirtualSlot1(&unk_22c, 4);
        Unk_10aa73c0(Out, unk_230);
    }
}
