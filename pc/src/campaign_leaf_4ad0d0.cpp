// campaign_leaf_4ad0d0.cpp -- one function at file offset 0x4ad0d0, preferred VA 0x10dad0d0.
// It stores Value, converted to network byte order by htons, in the unsigned short at offset 2.
// The class, method and member names are invented; the offset and the bytes are the binary's.

extern "C" __declspec(dllimport) unsigned short __stdcall htons(unsigned short Value);

class UnkType_10dad0d0
{
public:
    unsigned short unk_0;
    unsigned short unk_2;

    void Unk_10dad0d0(unsigned short Value);
};

// UnkType_10dad0d0::Unk_10dad0d0
void UnkType_10dad0d0::Unk_10dad0d0(unsigned short Value)
{
    unk_2 = htons(Value);
}
