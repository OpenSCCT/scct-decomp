// Work item 0336: RVA 0x10ea50, LTCG (this in ESI, ret 8).
// Appends a length-prefixed byte string into a 512-byte buffer and returns
// the space left. Class and member names are neutral: no symbols identify it.
typedef int INT;
typedef float FLOAT;
typedef unsigned char BYTE;

void appMemcpy(void *Dest, const void *Src, INT Count); // FUN_109040a0

class UnnamedClass_10ea50
{
public:
    BYTE Pad0[0x1cc];
    FLOAT BytesWritten;          // 0x1cc
    BYTE Pad1[0x47bc - 0x1d0];
    INT BufferCount;             // 0x47bc
    BYTE Buffer[0x200];          // 0x47c0

    INT Remaining() { return 0x200 - BufferCount; }
    INT AppendString(const void *Src, INT Len);
};

INT UnnamedClass_10ea50::AppendString(const void *Src, INT Len)
{
    if (Len <= 255 && Remaining() >= Len + 1)
    {
        BYTE *Dest = &Buffer[BufferCount];
        *Dest = (BYTE)Len;
        appMemcpy(Dest + 1, Src, Len);
        BufferCount += Len + 1;
        BytesWritten += Len;
    }
    return Remaining();
}

// Scaffolding for the link, not part of the unit.
INT Driver_10ea50(UnnamedClass_10ea50 *Obj, const void *Src, INT Len)
{
    return Obj->AppendString(Src, Len);
}
