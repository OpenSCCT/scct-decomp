// campaign_leaf_0b5d80.cpp -- one function at file offset 0xb5d80, preferred VA 0x109b5d80. It
// splits its argument into a high and a low 16-bit half and returns the address of the byte at the
// low half within its object when the high half equals the word at offset 0x10000, or is one less
// and the low half is at least the word at offset 0x10004; otherwise null. The class, method and
// member names are invented; the offset and the bytes are the binary's.

class UnkType_109b5d80
{
public:
    unsigned char unk_0[0x10000];
    unsigned int unk_10000;
    unsigned int unk_10004;

    unsigned char* Unk_109b5d80(unsigned int Handle);
};

// UnkType_109b5d80::Unk_109b5d80
unsigned char* UnkType_109b5d80::Unk_109b5d80(unsigned int Handle)
{
    unsigned int High = Handle >> 16;
    unsigned int Low = Handle & 0xffff;
    if ( High == unk_10000 || ( High + 1 == unk_10000 && Low >= unk_10004 ) )
    {
        return &unk_0[Low];
    }
    return 0;
}
