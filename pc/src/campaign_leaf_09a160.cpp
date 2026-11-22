// campaign_leaf_09a160.cpp -- one function at file offset 0x9a160, preferred VA 0x1099a160. It
// replaces the first word of the int array at offset 0x2b4, among its first count words (the count
// at 0x2b8), that equals its first argument, with its second argument. The class and method names
// are invented; the offset and the bytes are the binary's.

class UnkType_1099a160
{
public:
    void UnkReplace(int Old, int New);

private:
    unsigned char unk_00[0x2b4];    // not read by this function
    int *unk_2b4;
    int unk_2b8;
};

// UnkType_1099a160::UnkReplace
void UnkType_1099a160::UnkReplace(int Old, int New)
{
    for ( int i = 0; i < unk_2b8; ++i )
    {
        if ( unk_2b4[i] == Old )
        {
            unk_2b4[i] = New;
            return;
        }
    }
}
