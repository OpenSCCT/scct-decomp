// campaign_leaf_34bd00.cpp -- one function at file offset 0x34bd00, preferred VA 0x10c4bd00. It
// passes (Event, Other) to the method at 0x10bedc50; when Event holds 6 it clears the byte at
// 0x180 and passes the word at 0x2b4 of Other to the method at 0x10bf18d0, unless bit 0 of the
// word at 0x5cc of the object at 0x78 is set and the object the method at 0x10bf17b0 finds has
// its byte at 0x2d6 set. The class, method, member, local and parameter names are invented; the
// offsets, the constants and the bytes are the binary's.

class UnkType_10c4bd00_Other
{
public:
    unsigned char unk_0[0x2b4];
    int unk_2b4;
};

class UnkType_10c4bd00_Found
{
public:
    unsigned char unk_0[0x2d6];
    unsigned char unk_2d6;
};

class UnkType_10c4bd00_Settings
{
public:
    unsigned char unk_0[0x5cc];
    int unk_5cc;
};

class UnkType_10c4bd00
{
public:
    void Unk_10bedc50(int* Event, UnkType_10c4bd00_Other* Other);
    UnkType_10c4bd00_Found* Unk_10bf17b0(UnkType_10c4bd00* Owner, int Flags);
    void Unk_10bf18d0(int Value);
    void Unk_10c4bd00(int* Event, UnkType_10c4bd00_Other* Other);

    unsigned char unk_0[0x78];
    UnkType_10c4bd00_Settings* unk_78;
    unsigned char unk_7c[0x104];
    unsigned char unk_180;
};

// UnkType_10c4bd00::Unk_10c4bd00
void UnkType_10c4bd00::Unk_10c4bd00(int* Event, UnkType_10c4bd00_Other* Other)
{
    Unk_10bedc50(Event, Other);
    if ( *Event == 6 )
    {
        UnkType_10c4bd00_Found* Found;

        unk_180 = 0;
        if ( !(unk_78->unk_5cc & 1) )
        {
            Unk_10bf18d0(Other->unk_2b4);
            return;
        }
        Found = Unk_10bf17b0(this, 0);
        if ( Found == 0 || !Found->unk_2d6 )
        {
            Unk_10bf18d0(Other->unk_2b4);
        }
    }
}
