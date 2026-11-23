// campaign_leaf_6582d0.cpp -- thiscall method at VA 0x10f582d0 taking two values and a buffer:
// allocates a 12-byte record with the cdecl function at VA 0x10901480, stores the two values in it,
// allocates twice the count at 0x148 bytes, copies that many bytes of the buffer into it, stores it
// at 0x08 of the record, increments the counter at 0x160 and returns the record. The class, method
// and member names are invented; the offsets and addresses are the binary's.

extern "C" void* __cdecl memcpy(void* Dest, const void* Source, unsigned int Count);
#pragma intrinsic(memcpy)

void* __cdecl Unk_10901480(unsigned int Size);

struct UnkType_10f582d0_Record
{
    int unk_0;
    int unk_4;
    void* unk_8;
};

class UnkType_10f582d0
{
public:
    UnkType_10f582d0_Record* Unk_10f582d0(int First, int Second, const void* Data);

private:
    unsigned char unk_000[0x148];
    int unk_148;
    unsigned char unk_14c[0x160 - 0x14c];
    int unk_160;
};

// UnkType_10f582d0::Unk_10f582d0
UnkType_10f582d0_Record* UnkType_10f582d0::Unk_10f582d0(int First, int Second, const void* Data)
{
    UnkType_10f582d0_Record* Record;

    Record = (UnkType_10f582d0_Record*)Unk_10901480(sizeof(UnkType_10f582d0_Record));
    Record->unk_0 = First;
    Record->unk_4 = Second;
    Record->unk_8 = Unk_10901480(unk_148 * sizeof(unsigned short));
    memcpy(Record->unk_8, Data, unk_148 * sizeof(unsigned short));
    unk_160++;
    return Record;
}
