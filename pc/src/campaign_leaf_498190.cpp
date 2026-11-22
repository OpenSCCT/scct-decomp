// campaign_leaf_498190.cpp -- one function at file offset 0x498190, preferred VA 0x10d98190. It
// copies eight bytes from Source to Dest in reverse order. It has no this pointer. The function
// and parameter names are invented; the bytes are the binary's.

// Unk_10d98190
void Unk_10d98190(const unsigned char* Source, unsigned char* Dest)
{
    Dest[0] = Source[7];
    Dest[1] = Source[6];
    Dest[2] = Source[5];
    Dest[3] = Source[4];
    Dest[4] = Source[3];
    Dest[5] = Source[2];
    Dest[6] = Source[1];
    Dest[7] = Source[0];
}
