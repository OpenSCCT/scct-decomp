// campaign_leaf_4f9510.cpp -- constructor at VA 0x10df9510: constructs the member at offset 4 with
// the constructor at VA 0x10df4270, then clears the byte at offset 0. All names are invented.

class UnkType_10df4270
{
public:
    UnkType_10df4270();

private:
    int unk_00;
};

class UnkType_10df9510
{
public:
    UnkType_10df9510();

private:
    unsigned char unk_00;
    UnkType_10df4270 unk_04;
};

// UnkType_10df9510::UnkType_10df9510
UnkType_10df9510::UnkType_10df9510()
{
    unk_00 = 0;
}
