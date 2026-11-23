// campaign_leaf_75b300.cpp -- one function at file offset 0x75b300, preferred VA 0x1105b300. It
// releases the pointers at 0x44, 0x4c and 0x10 that are set through the stdcall function at VA
// 0x1103c870 (which forwards each to slot 2 of the object at VA 0x111c88a0), clearing them; when
// the handle at 0x18 is not -1 it passes it to the stdcall function at VA 0x110949b0 and sets it
// to -1; it then clears the word at 0xc. The class, method and member names are invented; the
// offsets and the addresses are the binary's.

void __stdcall Unk_1103c870(void* Pointer);
void __stdcall Unk_110949b0(int Handle);

class UnkType_1105b300
{
public:
    void Unk_1105b300();

    unsigned char unk_0[0xc];
    int unk_c;
    void* unk_10;
    int unk_14;
    int unk_18;
    unsigned char unk_1c[0x44 - 0x1c];
    void* unk_44;
    int unk_48;
    void* unk_4c;
};

// UnkType_1105b300::Unk_1105b300
void UnkType_1105b300::Unk_1105b300()
{
    if ( unk_44 != 0 )
    {
        Unk_1103c870(unk_44);
        unk_44 = 0;
    }
    if ( unk_4c != 0 )
    {
        Unk_1103c870(unk_4c);
        unk_4c = 0;
    }
    if ( unk_10 != 0 )
    {
        Unk_1103c870(unk_10);
        unk_10 = 0;
    }
    if ( unk_18 != -1 )
    {
        Unk_110949b0(unk_18);
        unk_18 = -1;
    }
    unk_c = 0;
}
