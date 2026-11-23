// campaign_leaf_74bb70.cpp -- one function at file offset 0x74bb70, preferred VA 0x1104bb70. It
// returns 0xffff0000 when the word at 0x4 of the record is set; otherwise it passes the word at
// 0x10 and 0 to the method at VA 0x11059980 of the object returned by the function at VA
// 0x11056900 (which returns the address of the global at VA 0x1132ea08) and returns its result.
// The type and function names are invented; the offsets and the addresses are the binary's.

class UnkType_1104bb70_Manager
{
public:
    int Unk_11059980(int Value, int Mode);
};

UnkType_1104bb70_Manager* Unk_11056900();

struct UnkType_1104bb70
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
};

// Unk_1104bb70
int __stdcall Unk_1104bb70(UnkType_1104bb70* Record)
{
    if ( Record->unk_4 == 0 )
    {
        return Unk_11056900()->Unk_11059980(Record->unk_10, 0);
    }
    return 0xffff0000;
}
