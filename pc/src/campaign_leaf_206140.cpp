// campaign_leaf_206140.cpp -- thiscall method at VA 0x10b06140. When the state word at 0x16fc is 7,
// it passes the two words of the 0x34-byte block at 0xb34 and the string "I LEAVE" to the stdcall
// function at VA 0x10ee8590 and sets the state to 5. It then passes the same two words to the
// method at VA 0x10efe270; when that returns true it clears the whole block. It returns that
// result. The class, method and member names are invented; the string is the binary's.

extern "C" void* __cdecl memset(void* Dest, int Value, unsigned int Count);

void __stdcall Unk_10ee8590(int First, int Second, const char* Text);

struct UnkType_10b06140_Block
{
    int unk_00;
    int unk_04;
    int unk_08[11];
};

class UnkType_10b06140
{
public:
    bool Unk_10b06140();
    bool Unk_10efe270(int First, int Second);

private:
    char unk_0000[0xb34];
    UnkType_10b06140_Block unk_0b34;
    char unk_0b68[0x16fc - 0xb68];
    int unk_16fc;
};

// UnkType_10b06140::Unk_10b06140
bool UnkType_10b06140::Unk_10b06140()
{
    if ( unk_16fc == 7 )
    {
        Unk_10ee8590(unk_0b34.unk_00, unk_0b34.unk_04, "I LEAVE");
        unk_16fc = 5;
    }
    bool bResult = Unk_10efe270(unk_0b34.unk_00, unk_0b34.unk_04);
    if ( bResult )
    {
        memset(&unk_0b34, 0, sizeof(unk_0b34));
    }
    return bResult;
}
