// campaign_leaf_57dcf0.cpp -- thiscall method at VA 0x10e7dcf0: formats Name, or "Name : Detail"
// when Detail is given and the two lengths add up to at most 190 characters, into a buffer of 256
// characters (through VA 0x10dffbe0, with lengths from VA 0x10dffdb0), then raises the depth at
// 0x00 and records, for the new depth, the result of the method at VA 0x10e7dc90 for the buffer
// (words from 0x1c) and a cleared flag (bytes from 0x10). guess: pushes a named scope. All names
// are invented; the addresses and the strings are the binary's.

int Unk_10dffdb0(const char* Text);
int Unk_10dffbe0(char* Buffer, const char* Format, ...);

class UnkType_10e7dcf0
{
public:
    void Unk_10e7dcf0(const char* Name, const char* Detail);

private:
    int Unk_10e7dc90(const char* Text);

    int unk_00;
    int unk_04[3];
    unsigned char unk_10[12];
    int unk_1c[12];
};

// UnkType_10e7dcf0::Unk_10e7dcf0
void UnkType_10e7dcf0::Unk_10e7dcf0(const char* Name, const char* Detail)
{
    char Buffer[256];

    if ( Detail && Unk_10dffdb0(Name) + Unk_10dffdb0(Detail) <= 190 )
    {
        Unk_10dffbe0(Buffer, "%s : %s", Name, Detail);
    }
    else
    {
        Unk_10dffbe0(Buffer, "%s", Name);
    }
    unk_00++;
    unk_1c[unk_00] = Unk_10e7dc90(Buffer);
    unk_10[unk_00] = 0;
}
