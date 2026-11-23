// campaign_leaf_4ad050.cpp -- one function at file offset 0x4ad050, preferred VA 0x10dad050.
// It stores Value, converted to network byte order by htonl, in the int at offset 4. The class,
// method and member names are invented; the offset and the bytes are the binary's.

extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long Value);

class UnkType_10dad050
{
public:
    unsigned long unk_0;
    unsigned long unk_4;

    void Unk_10dad050(unsigned long Value);
};

// UnkType_10dad050::Unk_10dad050
void UnkType_10dad050::Unk_10dad050(unsigned long Value)
{
    unk_4 = htonl(Value);
}
