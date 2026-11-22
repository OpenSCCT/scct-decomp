// campaign_leaf_1a8340.cpp -- one function at file offset 0x1a8340, preferred VA 0x10aa8340. Unless
// bit 4 of the byte at offset 0x28 is set, it stores at offset 0xac a 12-byte record built from the
// pointer at offset 0x78, -1 and a zero byte. Its two arguments are never read. The class, method
// and member names are invented; the offset and the bytes are the binary's.

struct UnkType_10aa8340_Record
{
    void* unk_0;
    int unk_4;
    unsigned char unk_8;

    UnkType_10aa8340_Record(void* First, int Second, unsigned char Third)
        : unk_0(First), unk_4(Second), unk_8(Third)
    {
    }
};

class UnkType_10aa8340
{
public:
    unsigned char unk_0[0x28];
    unsigned char unk_28;
    unsigned char unk_29[0x78 - 0x29];
    void* unk_78;
    unsigned char unk_7c[0xac - 0x7c];
    UnkType_10aa8340_Record unk_ac;

    void Unk_10aa8340(int First, int Second);
};

// UnkType_10aa8340::Unk_10aa8340
void UnkType_10aa8340::Unk_10aa8340(int First, int Second)
{
    if ( !( unk_28 & 4 ) )
    {
        unk_ac = UnkType_10aa8340_Record(unk_78, -1, 0);
    }
}
