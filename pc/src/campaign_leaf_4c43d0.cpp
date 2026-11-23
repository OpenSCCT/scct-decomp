// campaign_leaf_4c43d0.cpp -- one function at file offset 0x4c43d0, preferred VA 0x10dc43d0.
// The constructor installs the vtable at 0x11143a30 and converts the wide Text into the 0x40-byte
// buffer at offset 4 with the function at 0x10dbd830. The class, function, member and parameter
// names are invented; the offset and the bytes are the binary's.

int Unk_10dbd830(const unsigned short* Text, char* Buffer, int Capacity);

class UnkType_10dc43d0
{
public:
    char unk_4[0x40];

    UnkType_10dc43d0(const unsigned short* Text);

    virtual void VirtualSlot0();
};

// UnkType_10dc43d0::UnkType_10dc43d0
UnkType_10dc43d0::UnkType_10dc43d0(const unsigned short* Text)
{
    Unk_10dbd830(Text, unk_4, 0x40);
}
