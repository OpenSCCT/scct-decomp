// campaign_leaf_4c41b0.cpp -- one function at file offset 0x4c41b0, preferred VA 0x10dc41b0.
// It passes 3 and the message "An error has been detected in the DOCore." to the cdecl function at
// 0x10d97ba0 and then sets the byte at offset 0x40. The class, function, method and member names
// are invented; the offset and the bytes are the binary's.

void Unk_10d97ba0(int Kind, const unsigned short* Message);

class UnkType_10dc41b0
{
public:
    unsigned char unk_0[0x40];
    bool unk_40;

    void Unk_10dc41b0();
};

// UnkType_10dc41b0::Unk_10dc41b0
void UnkType_10dc41b0::Unk_10dc41b0()
{
    Unk_10d97ba0(3, L"An error has been detected in the DOCore.");
    unk_40 = true;
}
