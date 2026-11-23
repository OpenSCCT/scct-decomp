// campaign_leaf_4ad090.cpp -- one function at file offset 0x4ad090, preferred VA 0x10dad090.
// It converts the address at offset 4 to dotted text with inet_ntoa, widens it into Buffer with
// the function at 0x10dbd810 and returns true. The class, function, method, member and parameter
// names are invented; the offset and the bytes are the binary's.

struct in_addr
{
    unsigned long S_addr;
};

extern "C" __declspec(dllimport) char* __stdcall inet_ntoa(in_addr Address);

int Unk_10dbd810(const char* Text, unsigned short* Buffer, int Capacity);

class UnkType_10dad090
{
public:
    int unk_0;
    in_addr unk_4;

    bool Unk_10dad090(unsigned short* Buffer, int Capacity);
};

// UnkType_10dad090::Unk_10dad090
bool UnkType_10dad090::Unk_10dad090(unsigned short* Buffer, int Capacity)
{
    Unk_10dbd810(inet_ntoa(unk_4), Buffer, Capacity);
    return true;
}
