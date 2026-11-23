// campaign_leaf_21c040.cpp -- a member function at VA 0x10b1c040 taking nine arguments: when the
// free function at VA 0x10ccae40, given the second argument and the narrow string at 0x2406,
// returns zero, it copies at most 15 characters of the second argument to 0x2406 with strncpy (the
// C runtime's, named in pc/evidence/library-functions.tsv); then, when the int at 0x16fc is 1, it
// copies at most 9 characters of the seventh argument to 0x2449, sets the int at 0x16fc to 2 and
// passes the string at 0x2406 to the function at VA 0x10ee8e10. The class, method, member and
// parameter names are invented; the offsets, counts and addresses are the binary's.

extern "C" char* __cdecl strncpy(char* Dest, const char* Source, unsigned int Count);

int Unk_10ccae40(const char* First, const char* Second);
void __stdcall Unk_10ee8e10(const char* Name);

class UnkType_10b1c040
{
public:
    void Unk_10b1c040(int, const char* Name, int, int, int, int, const char* Code, int, int);

private:
    unsigned char unk_0000[0x16fc];
    int unk_16fc;
    unsigned char unk_1700[0x2406 - 0x1700];
    char unk_2406[0x2449 - 0x2406];
    char unk_2449[9];
};

// UnkType_10b1c040::Unk_10b1c040
void UnkType_10b1c040::Unk_10b1c040(int, const char* Name, int, int, int, int,
                                    const char* Code, int, int)
{
    if ( Unk_10ccae40(Name, unk_2406) == 0 )
    {
        strncpy(unk_2406, Name, 15);
        if ( unk_16fc == 1 )
        {
            strncpy(unk_2449, Code, 9);
            unk_16fc = 2;
            Unk_10ee8e10(unk_2406);
        }
    }
}
