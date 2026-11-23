// campaign_leaf_681ea0.cpp -- stdcall function at VA 0x10f81ea0 taking a structure: calls a fixed
// sequence of stdcall initialisers with it (VA 0x10fb2680 with 0; unless the value at 0xb0 is set,
// VA 0x10fb1af0, 0x10fb1250 and 0x10fb0730 with 0; then VA 0x10fb00a0), raises error 1 when the
// value at 0xb4 is set, otherwise calls VA 0x10faf000 or VA 0x10fae2f0 depending on the value at
// 0xec, calls VA 0x10fad490 with whether 0xa8 exceeds 1 or 0xb8 is set, VA 0x10facc20 with 0 and
// VA 0x10f81e50, and finally the function at 0x18 of the structure at 0x04 and the function at
// 0x00 of the structure at 0x164. The shape follows the IJG JPEG library's compressor master
// initialiser, but no evidence names it: the type, function and member names are invented; the
// offsets and addresses are the binary's.

struct UnkType_10f81ea0;

struct UnkType_10f81ea0_Error
{
    void (__stdcall* unk_00)(UnkType_10f81ea0* Info);
    unsigned char unk_04[0x14 - 0x4];
    int unk_14;
};

struct UnkType_10f81ea0_Memory
{
    unsigned char unk_00[0x18];
    void (__stdcall* unk_18)(UnkType_10f81ea0* Info);
};

struct UnkType_10f81ea0_Methods
{
    void (__stdcall* unk_00)(UnkType_10f81ea0* Info);
};

struct UnkType_10f81ea0
{
    UnkType_10f81ea0_Error* unk_000;
    UnkType_10f81ea0_Memory* unk_004;
    unsigned char unk_008[0xa8 - 0x8];
    int unk_0a8;
    int unk_0ac;
    int unk_0b0;
    int unk_0b4;
    int unk_0b8;
    unsigned char unk_0bc[0xec - 0xbc];
    int unk_0ec;
    unsigned char unk_0f0[0x164 - 0xf0];
    UnkType_10f81ea0_Methods* unk_164;
};

void __stdcall Unk_10fb2680(UnkType_10f81ea0* Info, int Flag);
void __stdcall Unk_10fb1af0(UnkType_10f81ea0* Info);
void __stdcall Unk_10fb1250(UnkType_10f81ea0* Info);
void __stdcall Unk_10fb0730(UnkType_10f81ea0* Info, int Flag);
void __stdcall Unk_10fb00a0(UnkType_10f81ea0* Info);
void __stdcall Unk_10faf000(UnkType_10f81ea0* Info);
void __stdcall Unk_10fae2f0(UnkType_10f81ea0* Info);
void __stdcall Unk_10fad490(UnkType_10f81ea0* Info, int Flag);
void __stdcall Unk_10facc20(UnkType_10f81ea0* Info, int Flag);
void __stdcall Unk_10f81e50(UnkType_10f81ea0* Info);

// Unk_10f81ea0
void __stdcall Unk_10f81ea0(UnkType_10f81ea0* Info)
{
    UnkType_10f81ea0_Error* Error;

    Unk_10fb2680(Info, 0);
    if ( !Info->unk_0b0 )
    {
        Unk_10fb1af0(Info);
        Unk_10fb1250(Info);
        Unk_10fb0730(Info, 0);
    }
    Unk_10fb00a0(Info);
    if ( Info->unk_0b4 )
    {
        Error = Info->unk_000;
        Error->unk_14 = 1;
        Error->unk_00(Info);
    }
    else if ( Info->unk_0ec )
    {
        Unk_10faf000(Info);
    }
    else
    {
        Unk_10fae2f0(Info);
    }
    Unk_10fad490(Info, Info->unk_0a8 > 1 || Info->unk_0b8);
    Unk_10facc20(Info, 0);
    Unk_10f81e50(Info);
    Info->unk_004->unk_18(Info);
    Info->unk_164->unk_00(Info);
}
