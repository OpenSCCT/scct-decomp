// campaign_leaf_4f4d00.cpp -- constructor at VA 0x10df4d00: runs the empty base constructor at
// VA 0x10d9d560 and clears the byte at offset 6. All names are invented.

class UnkType_10d9d560
{
public:
    UnkType_10d9d560();
};

class UnkType_10df4d00 : public UnkType_10d9d560
{
public:
    UnkType_10df4d00();

private:
    int unk_00;
    short unk_04;
    unsigned char unk_06;
};

// UnkType_10df4d00::UnkType_10df4d00
UnkType_10df4d00::UnkType_10df4d00()
{
    unk_06 = 0;
}
