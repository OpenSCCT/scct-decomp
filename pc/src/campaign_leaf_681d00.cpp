// campaign_leaf_681d00.cpp -- stdcall function at VA 0x10f81d00 taking one structure: writes the
// bytes 0xff and 0xd9 through the output structure its member 0x18 points to (next byte at 0x00,
// bytes free at 0x04, a flush function at 0x0c). When the buffer fills and the flush function
// returns zero it stores 0x18 at 0x14 of the structure at 0x00 and calls the function at its start.
// The shape follows the IJG JPEG library's end-of-image marker writer, but no evidence names it: the
// type, function and member names are invented; the offsets are the binary's.

struct UnkType_10f81d00;

struct UnkType_10f81d00_Error
{
    void (__stdcall* unk_00)(UnkType_10f81d00* Info);
    unsigned char unk_04[0x14 - 0x4];
    int unk_14;
};

struct UnkType_10f81d00_Output
{
    unsigned char* unk_00;
    unsigned int unk_04;
    void* unk_08;
    int (__stdcall* unk_0c)(UnkType_10f81d00* Info);
};

struct UnkType_10f81d00
{
    UnkType_10f81d00_Error* unk_00;
    unsigned char unk_04[0x18 - 0x4];
    UnkType_10f81d00_Output* unk_18;
};

// EmitByte: writes one byte to the output, flushing it when full. Name invented.
static void EmitByte(UnkType_10f81d00* Info, int Value)
{
    UnkType_10f81d00_Output* Output = Info->unk_18;
    UnkType_10f81d00_Error* Error;
    unsigned char* Next;

    Next = Output->unk_00;
    *Next = (unsigned char)Value;
    Output->unk_00 = Next + 1;
    if ( --Output->unk_04 == 0 )
    {
        if ( !Output->unk_0c(Info) )
        {
            Error = Info->unk_00;
            Error->unk_14 = 0x18;
            Error->unk_00(Info);
        }
    }
}

// Unk_10f81d00
void __stdcall Unk_10f81d00(UnkType_10f81d00* Info)
{
    EmitByte(Info, 0xff);
    EmitByte(Info, 0xd9);
}
