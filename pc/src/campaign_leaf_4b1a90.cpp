// campaign_leaf_4b1a90.cpp -- one function at file offset 0x4b1a90, preferred VA 0x10db1a90.
// It returns the int at offset 0 when the method at 0x10d80480 returns true, and 0 otherwise.
// The class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10db1a90
{
public:
    int unk_0;

    bool Unk_10d80480();
    int Unk_10db1a90();
};

// UnkType_10db1a90::Unk_10db1a90
int UnkType_10db1a90::Unk_10db1a90()
{
    if ( !Unk_10d80480() )
    {
        return 0;
    }
    return unk_0;
}
