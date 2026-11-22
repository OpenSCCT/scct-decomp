// campaign_leaf_135590.cpp -- adds 1 to the dword at offset 0xedc of this while it is below 30. File
// offset 0x135590, VA 0x10a35590. The class and method names are invented; the offsets are the
// binary's.

class UnkType_10a35590
{
public:
    void IncUnkEdcUpTo30();

private:
    unsigned char unk_00[0xedc];    // not read by this function
    int unk_edc;
};

// UnkType_10a35590::IncUnkEdcUpTo30
void UnkType_10a35590::IncUnkEdcUpTo30()
{
    if ( unk_edc < 30 )
    {
        unk_edc++;
    }
}
