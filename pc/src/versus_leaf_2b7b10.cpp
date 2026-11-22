// versus_leaf_2b7b10.cpp -- stores the sum of a byte argument and two bytes of a source record at 0x49, and the
// source record's dword at 0x4a, at file offset 0x2b7b10 (VA 0x10bb7b10). The class, record and method names are
// invented; the offsets, the argument sizes and the calling convention are the binary's.

#pragma pack(push, 1)
struct UnkSource_10bb7b10
{
    unsigned char unk_00[2];
    unsigned char unk_02;               // read by SetUnk49Unk4a
    unsigned char unk_03;               // read by SetUnk49Unk4a
};

class UnkType_10bb7b10
{
public:
    void SetUnk49Unk4a(unsigned char Add, UnkSource_10bb7b10 *Source);

private:
    unsigned char unk_00[0x49];
    unsigned char unk_49;               // written by SetUnk49Unk4a
    int unk_4a;                         // written by SetUnk49Unk4a
};
#pragma pack(pop)

// UnkType_10bb7b10::SetUnk49Unk4a
// The function pops its two arguments (ret 8).
void UnkType_10bb7b10::SetUnk49Unk4a(unsigned char Add, UnkSource_10bb7b10 *Source)
{
    unk_49 = Source->unk_03 + Source->unk_02 + Add;
    unk_4a = *(int *)Source;
}
