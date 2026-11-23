// campaign_leaf_76c620.cpp -- one function at file offset 0x76c620, preferred VA 0x1106c620. A
// constructor: it runs the base constructor at VA 0x11062f40, zeroes the words at 0x64 and 0x4,
// installs the vtable at VA 0x11176ab8 and stores the address of the function at VA 0x1106c5e0
// at 0x44. The class names are invented; the offsets and the addresses are the binary's.

void Unk_1106c5e0(void* Object);

class UnkType_1106c620_Base
{
public:
    UnkType_1106c620_Base();
    virtual ~UnkType_1106c620_Base();

    int unk_4;
    unsigned char unk_8[0x44 - 0x8];
    void (*unk_44)(void* Object);
    unsigned char unk_48[0x64 - 0x48];
};

class UnkType_1106c620 : public UnkType_1106c620_Base
{
public:
    UnkType_1106c620();
    virtual ~UnkType_1106c620();

    int unk_64;
};

// UnkType_1106c620::UnkType_1106c620
UnkType_1106c620::UnkType_1106c620()
{
    unk_64 = 0;
    unk_4 = 0;
    unk_44 = Unk_1106c5e0;
}
