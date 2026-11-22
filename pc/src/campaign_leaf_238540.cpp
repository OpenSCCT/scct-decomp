// campaign_leaf_238540.cpp -- a member function at VA 0x10b38540 that copies at most 15 characters
// of the narrow string at 0x44 to the buffer its argument points to, with strncpy (the C runtime's,
// named in pc/evidence/library-functions.tsv). The class, method and member names are invented; the
// offsets are the binary's.

extern "C" char* __cdecl strncpy(char* Dest, const char* Source, unsigned int Count);

class UnkType_10b38540
{
public:
    void Unk_10b38540(char* Dest);

private:
    unsigned char unk_00[0x44];
    char unk_44[16];
};

// UnkType_10b38540::Unk_10b38540
void UnkType_10b38540::Unk_10b38540(char* Dest)
{
    strncpy(Dest, unk_44, 15);
}
