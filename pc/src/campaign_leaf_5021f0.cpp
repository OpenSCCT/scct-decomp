// campaign_leaf_5021f0.cpp -- method at VA 0x10e021f0: copies a count of bytes out of the buffer at
// 0x0c from the position at 0x10 up to the limit at 0x14 (copy function at VA 0x10dffe80),
// refilling the buffer through the method at VA 0x10e02100 whenever it runs short, and returns the
// count copied: all of it, or what was copied before a refill failed. The class, method and member
// names are invented; the offsets and the addresses are the binary's.

void* Unk_10dffe80(void* Destination, const void* Source, int Count);

class UnkType_10e021f0
{
public:
    int Unk_10e021f0(char* Destination, int Count);
    int Unk_10e02100();

    unsigned char unk_00[0x0c];
    char* unk_0c;
    int unk_10;
    int unk_14;
};

// UnkType_10e021f0::Unk_10e021f0
int UnkType_10e021f0::Unk_10e021f0(char* Destination, int Count)
{
    int Left = Count;
    int Available = unk_14 - unk_10;
    while ( Left > Available )
    {
        Unk_10dffe80(Destination, unk_0c + unk_10, Available);
        Destination += Available;
        Left -= Available;
        unk_10 += Available;
        if ( Unk_10e02100() != 0 )
        {
            return Count - Left;
        }
        Available = unk_14 - unk_10;
    }
    Unk_10dffe80(Destination, unk_0c + unk_10, Left);
    unk_10 += Left;
    return Count;
}
