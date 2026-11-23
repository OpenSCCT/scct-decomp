// campaign_leaf_75c350.cpp -- one function at file offset 0x75c350, preferred VA 0x1105c350. When
// the record at 0x8 holds a pointer at 0x30 it releases it through the stdcall function at VA
// 0x1103c870 (which forwards it to slot 2 of the object at VA 0x111c88a0) and clears it; it then
// clears the record pointer. The class, method and member names are invented; the offsets and the
// callee's address are the binary's.

void __stdcall Unk_1103c870(void* Pointer);

struct UnkType_1105c350_Record
{
    unsigned char unk_0[0x30];
    void* unk_30;
};

class UnkType_1105c350
{
public:
    void Unk_1105c350();

    int unk_0;
    int unk_4;
    UnkType_1105c350_Record* unk_8;
};

// UnkType_1105c350::Unk_1105c350
void UnkType_1105c350::Unk_1105c350()
{
    if ( unk_8->unk_30 != 0 )
    {
        Unk_1103c870(unk_8->unk_30);
        unk_8->unk_30 = 0;
    }
    unk_8 = 0;
}
