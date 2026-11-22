// campaign_leaf_238510.cpp -- a member function at VA 0x10b38510: when the byte at 0x3c is set it
// calls the member at VA 0x10b65820, clears the int at 0x40 and clears the byte; it returns true.
// The class, method and member names are invented; the offsets and addresses are the binary's.

class UnkType_10b38510
{
public:
    void Unk_10b65820();
    bool Unk_10b38510();

private:
    unsigned char unk_00[0x3c];
    bool unk_3c;
    unsigned char unk_3d[3];
    int unk_40;
};

// UnkType_10b38510::Unk_10b38510
bool UnkType_10b38510::Unk_10b38510()
{
    if ( unk_3c )
    {
        Unk_10b65820();
        unk_40 = 0;
        unk_3c = false;
    }
    return true;
}
