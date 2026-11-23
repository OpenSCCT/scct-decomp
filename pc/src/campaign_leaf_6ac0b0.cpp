// campaign_leaf_6ac0b0.cpp -- stdcall function at VA 0x10fac0b0 taking three arguments: stores the
// result of the function at VA 0x110938b8 at 0x0c of the second; when it is null, stores 0x3f at
// 0x14 of the error structure the first points to, copies an empty string into its buffer at 0x18
// with strncpy (at most 80 bytes) and calls the error structure's function at 0x00. It then fills
// the second structure with three function addresses. The third argument is unused. The shape
// follows the IJG JPEG library's backing-store opener, but no evidence names it: the type, function
// and member names are invented; the offsets and addresses are the binary's.

extern "C" char* __cdecl strncpy(char* Dest, const char* Source, unsigned int Count);

struct UnkType_10fac0b0;

struct UnkType_10fac0b0_Error
{
    void (__stdcall* unk_00)(UnkType_10fac0b0* Info);
    unsigned char unk_04[0x14 - 0x4];
    int unk_14;
    char unk_18[80];
};

struct UnkType_10fac0b0
{
    UnkType_10fac0b0_Error* unk_00;
};

struct UnkType_10fac0b0_Store
{
    void (__stdcall* unk_00)(UnkType_10fac0b0* Info, UnkType_10fac0b0_Store* Store);
    void (__stdcall* unk_04)(UnkType_10fac0b0* Info, UnkType_10fac0b0_Store* Store);
    void (__stdcall* unk_08)(UnkType_10fac0b0* Info, UnkType_10fac0b0_Store* Store);
    void* unk_0c;
};

void* __cdecl Unk_110938b8();
void __stdcall Unk_10fabfd0(UnkType_10fac0b0* Info, UnkType_10fac0b0_Store* Store);
void __stdcall Unk_10fac030(UnkType_10fac0b0* Info, UnkType_10fac0b0_Store* Store);
void __stdcall Unk_10fac090(UnkType_10fac0b0* Info, UnkType_10fac0b0_Store* Store);

// Unk_10fac0b0
void __stdcall Unk_10fac0b0(UnkType_10fac0b0* Info, UnkType_10fac0b0_Store* Store, long Size)
{
    UnkType_10fac0b0_Error* Error;

    if ( ( Store->unk_0c = Unk_110938b8() ) == 0 )
    {
        Error = Info->unk_00;
        Error->unk_14 = 0x3f;
        strncpy(Error->unk_18, "", 80);
        Info->unk_00->unk_00(Info);
    }
    Store->unk_00 = Unk_10fabfd0;
    Store->unk_04 = Unk_10fac030;
    Store->unk_08 = Unk_10fac090;
}
