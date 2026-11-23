// campaign_leaf_76ad50.cpp -- one function at file offset 0x76ad50, preferred VA 0x1106ad50. A
// constructor: it runs the base constructor at VA 0x11062f40, zeroes the words at 0x68, 0x6c, 0x70
// and 0x4, installs the vtable at VA 0x11176958, stores -1 at 0x64 and the address of the function
// at VA 0x1106ace0 at 0x44. The class names are invented; the offsets and the addresses are the
// binary's.

void Unk_1106ace0(void* Object);

class UnkType_1106ad50_Base
{
public:
    UnkType_1106ad50_Base();
    virtual ~UnkType_1106ad50_Base();

    int unk_4;
    unsigned char unk_8[0x44 - 0x8];
    void (*unk_44)(void* Object);
    unsigned char unk_48[0x64 - 0x48];
    int unk_64;
};

class UnkType_1106ad50 : public UnkType_1106ad50_Base
{
public:
    UnkType_1106ad50();
    virtual ~UnkType_1106ad50();

    int unk_68;
    int unk_6c;
    int unk_70;
};

// UnkType_1106ad50::UnkType_1106ad50
UnkType_1106ad50::UnkType_1106ad50()
{
    unk_68 = 0;
    unk_6c = 0;
    unk_70 = 0;
    unk_4 = 0;
    unk_64 = -1;
    unk_44 = Unk_1106ace0;
}
