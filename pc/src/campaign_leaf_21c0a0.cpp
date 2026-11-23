// campaign_leaf_21c0a0.cpp -- a member function at VA 0x10b1c0a0 taking a byte, a narrow string, a
// 16-bit value and an int: when the byte at 0x23e9 is clear and the byte argument is 0x26 it copies
// at most 0x80 characters of the string to 0x1f5a with strncpy (the C runtime's, named in
// pc/evidence/library-functions.tsv), stores the 16-bit value at 0x1fdc and sets the int at 0x16f0
// to 7. Otherwise, when the byte at 0x23e9 is clear, it calls the member at VA 0x10b090d0 with 0,
// the int argument and 1; in both of those cases it then sets the int at 0x16f0 to 1, calls the
// member at VA 0x10efe000 and sets the int at 0x16f8 to 1. The class, method, member and parameter
// names are invented; the offsets, constants and addresses are the binary's.

extern "C" char* __cdecl strncpy(char* Dest, const char* Source, unsigned int Count);

class UnkType_10b1c0a0
{
public:
    void Unk_10b090d0(int First, int Value, int Third);
    void Unk_10efe000();
    void Unk_10b1c0a0(unsigned char Key, const char* Text, unsigned short Code, int Value);

private:
    unsigned char unk_0000[0x16f0];
    int unk_16f0;
    unsigned char unk_16f4[0x16f8 - 0x16f4];
    int unk_16f8;
    unsigned char unk_16fc[0x1f5a - 0x16fc];
    char unk_1f5a[0x80];
    unsigned char unk_1fda[0x1fdc - 0x1fda];
    unsigned short unk_1fdc;
    unsigned char unk_1fde[0x23e9 - 0x1fde];
    bool unk_23e9;
};

// UnkType_10b1c0a0::Unk_10b1c0a0
void UnkType_10b1c0a0::Unk_10b1c0a0(unsigned char Key, const char* Text, unsigned short Code,
                                    int Value)
{
    if ( !unk_23e9 )
    {
        if ( Key == 0x26 )
        {
            strncpy(unk_1f5a, Text, 0x80);
            unk_1fdc = Code;
            unk_16f0 = 7;
            return;
        }
        Unk_10b090d0(0, Value, 1);
    }
    unk_16f0 = 1;
    Unk_10efe000();
    unk_16f8 = 1;
}
