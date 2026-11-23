// campaign_leaf_5ee510.cpp -- thiscall method at VA 0x10eee510 taking a stream: reads it in blocks
// of up to 0x400 bytes with the cdecl function at VA 0x10f35e5e (buffer, 1, 0x400, stream) and
// passes each block and its length to the method at VA 0x10eef8e0 of the object at 0x24, until a
// read returns zero; returns true. The class, method and member names are invented; the offsets
// and addresses are the binary's.

unsigned int __cdecl Unk_10f35e5e(void* Buffer, unsigned int Size, unsigned int Count, void* Stream);

class UnkType_10eee510_Target
{
public:
    void Unk_10eef8e0(const unsigned char* Data, unsigned int Length);
};

class UnkType_10eee510
{
public:
    bool Unk_10eee510(void* Stream);

private:
    unsigned char unk_00[0x24];
    UnkType_10eee510_Target* unk_24;
};

// UnkType_10eee510::Unk_10eee510
bool UnkType_10eee510::Unk_10eee510(void* Stream)
{
    unsigned char Buffer[0x400];
    unsigned int Length;

    while ( ( Length = Unk_10f35e5e(Buffer, 1, sizeof(Buffer), Stream) ) != 0 )
    {
        unk_24->Unk_10eef8e0(Buffer, Length);
    }
    return true;
}
