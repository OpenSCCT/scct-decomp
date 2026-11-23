// campaign_leaf_5ffd00.cpp -- thiscall method at VA 0x10effd00 taking three strings and a value:
// copies the strings with strncpy into the buffers at 0x04 (at most 15 bytes), 0x14 (16) and 0x25
// (32), then passes all four arguments to the method at VA 0x10f14770 of the object at 0x150. The
// class, method and member names are invented; the offsets and addresses are the binary's.

extern "C" char* __cdecl strncpy(char* Dest, const char* Source, unsigned int Count);

class UnkType_10effd00_Target
{
public:
    void Unk_10f14770(const char* First, const char* Second, const char* Third, int Value);
};

class UnkType_10effd00
{
public:
    void Unk_10effd00(const char* First, const char* Second, const char* Third, int Value);

private:
    int unk_000;
    char unk_004[0x10];
    char unk_014[0x11];
    char unk_025[0x21];
    unsigned char unk_046[0x150 - 0x46];
    UnkType_10effd00_Target* unk_150;
};

// UnkType_10effd00::Unk_10effd00
void UnkType_10effd00::Unk_10effd00(const char* First, const char* Second, const char* Third, int Value)
{
    strncpy(unk_004, First, 0xf);
    strncpy(unk_014, Second, 0x10);
    strncpy(unk_025, Third, 0x20);
    unk_150->Unk_10f14770(First, Second, Third, Value);
}
