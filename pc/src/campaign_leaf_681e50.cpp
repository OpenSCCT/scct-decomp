// campaign_leaf_681e50.cpp -- stdcall function at VA 0x10f81e50 taking one structure: allocates 0x20
// bytes through the function at 0x00 of the structure its member 0x04 points to (with the arguments
// structure, 1, 0x20), stores the block at 0x164 and fills it with seven function addresses and a
// zero. The shape follows the IJG JPEG library's module initialisers, but no evidence names it: the
// type, function and member names are invented; the offsets and addresses are the binary's.

struct UnkType_10f81e50;

struct UnkType_10f81e50_Memory
{
    void* (__stdcall* unk_0)(UnkType_10f81e50* Info, int Pool, unsigned int Size);
};

struct UnkType_10f81e50_Methods
{
    void (__stdcall* unk_00)(UnkType_10f81e50* Info);
    void (__stdcall* unk_04)(UnkType_10f81e50* Info);
    void (__stdcall* unk_08)(UnkType_10f81e50* Info);
    void (__stdcall* unk_0c)(UnkType_10f81e50* Info);
    void (__stdcall* unk_10)(UnkType_10f81e50* Info);
    void (__stdcall* unk_14)(UnkType_10f81e50* Info);
    void (__stdcall* unk_18)(UnkType_10f81e50* Info);
    int unk_1c;
};

struct UnkType_10f81e50
{
    void* unk_000;
    UnkType_10f81e50_Memory* unk_004;
    unsigned char unk_008[0x164 - 0x8];
    UnkType_10f81e50_Methods* unk_164;
};

void __stdcall Unk_10f81ac0(UnkType_10f81e50* Info);
void __stdcall Unk_10f81b50(UnkType_10f81e50* Info);
void __stdcall Unk_10f81c40(UnkType_10f81e50* Info);
void __stdcall Unk_10f81d00(UnkType_10f81e50* Info);
void __stdcall Unk_10f81d60(UnkType_10f81e50* Info);
void __stdcall Unk_10f81a10(UnkType_10f81e50* Info);
void __stdcall Unk_10f81a90(UnkType_10f81e50* Info);

// Unk_10f81e50
void __stdcall Unk_10f81e50(UnkType_10f81e50* Info)
{
    UnkType_10f81e50_Methods* Methods;

    Methods = (UnkType_10f81e50_Methods*)Info->unk_004->unk_0(Info, 1, sizeof(UnkType_10f81e50_Methods));
    Info->unk_164 = Methods;
    Methods->unk_00 = Unk_10f81ac0;
    Methods->unk_04 = Unk_10f81b50;
    Methods->unk_08 = Unk_10f81c40;
    Methods->unk_0c = Unk_10f81d00;
    Methods->unk_10 = Unk_10f81d60;
    Methods->unk_14 = Unk_10f81a10;
    Methods->unk_18 = Unk_10f81a90;
    Methods->unk_1c = 0;
}
