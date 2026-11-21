// Work item 0041: Versus RVA 0x9ee0-0xa12e.
// A buffered, compressing archive writer: data is gathered into a 15 MB
// buffer, compressed in blocks and handed to an inner archive.
// Names are neutral (UnnamedClass_9ee0); field roles inferred from use.

void* __cdecl appMemcpy_409040a0(void* Dest, const void* Src, int Count);   // FUN_109040a0
int __cdecl compress_10b21c99(unsigned char* Dest, unsigned long* DestLen,
                              const unsigned char* Src, unsigned long SrcLen); // FUN_10b21c99 (zlib compress)

enum { BUFFER_SIZE = 0xf00000, COMPRESSED_SIZE = 0xf01000 };

class InnerArchive_9ee0
{
public:
    virtual ~InnerArchive_9ee0();
    virtual void Serialize(void* Data, int Length);    // slot 1 (+4)
    virtual void Slot2(); virtual void Slot3(); virtual void Slot4();
    virtual void Slot5(); virtual void Slot6(); virtual void Slot7();
    virtual void Slot8(); virtual void Slot9(); virtual void Slot10();
    virtual void Slot11(); virtual void Slot12(); virtual void Slot13();
    virtual void Slot14(); virtual void Slot15(); virtual void Slot16();
    virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual int  Close();                               // slot 20 (+0x50)
};

class UnnamedClass_9ee0
{
public:
    virtual void Slot0(); virtual void Slot1(); virtual void Slot2();
    virtual void Slot3(); virtual void Slot4(); virtual void Slot5();
    virtual void Slot6(); virtual void Slot7(); virtual void Slot8();
    virtual void Slot9(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14();
    virtual void Slot15(); virtual void Slot16(); virtual void Slot17();
    virtual void Slot18();
    virtual void Flush();                               // slot 19 (+0x4c)

    int Pad04[10];          // 0x04..0x28
    int ArIsError;          // 0x2c
    int Pad30[4];           // 0x30..0x3c
    InnerArchive_9ee0* Inner; // 0x40
    int TotalWritten;       // 0x44
    int Count;              // 0x48
    int Extra;              // 0x4c
    unsigned char Buffer[BUFFER_SIZE];          // 0x50
    int BlockHeader[2];                          // 0xf00050
    unsigned char Compressed[0xf00ff8];          // 0xf00058
    int TotalUncompressed;                       // 0x1e01050
    int TotalCompressed;                         // 0x1e01054

    int Pending() const { return Count + Extra; }

    int Close();
    void Serialize(void* Data, int Length);
    void CompressBlock();
};

int UnnamedClass_9ee0::Close()
{
    if (Inner)
    {
        Flush();
        ArIsError = Inner->Close() == 0;
        delete Inner;
        Inner = 0;
    }
    return !ArIsError;
}

void UnnamedClass_9ee0::Serialize(void* Data, int Length)
{
    TotalWritten += Length;
    int Avail;
    while (Length > (Avail = BUFFER_SIZE - Count))
    {
        appMemcpy_409040a0(&Buffer[Count], Data, Avail);
        Count += Avail;
        Length -= Avail;
        Data = (unsigned char*)Data + Avail;
        Flush();
    }
    if (Length)
    {
        appMemcpy_409040a0(&Buffer[Count], Data, Length);
        Count += Length;
    }
}

void UnnamedClass_9ee0::CompressBlock()
{
    if (Pending())
    {
        unsigned long CompressedSize = COMPRESSED_SIZE;
        compress_10b21c99(Compressed, &CompressedSize, Buffer, Pending());
        TotalUncompressed += Pending();
        TotalCompressed += CompressedSize;
        BlockHeader[1] = CompressedSize;
        BlockHeader[0] = Pending();
        Inner->Serialize(BlockHeader, CompressedSize + 8);
    }
    Count = 0;
    Extra = 0;
}

// Not reproduced here (link-time-generated code with custom conventions):
//  0x9ee0 constructor: this in EAX, inner archive in ESI; FArchive base init
//         (ArVer 0xaf, ArNetVer 2000, ArIsSaving 1, ArIsPersistent 1,
//         ArMaxSerializeSize -1, ...) then vtable 0x10c0e388.
//  0x9f50 destructor: this on the stack, ret 4, EH frame; inlined Close()
//         with Flush called through vtable slot 0x10c0e3d4, then FArchive
//         vtable 0x10c0e918.
