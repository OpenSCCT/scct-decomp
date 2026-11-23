// campaign_leaf_767c20.cpp -- one function at file offset 0x767c20, preferred VA 0x11067c20. For
// each of the objects at 0x24, 0x28, 0x2c and 0x30 that is set it passes that member's address to
// its release function (VA 0x1106f8a0, 0x11061eb0, 0x1106eae0 and 0x1106e6d0); it returns 0. The
// class, method and member names are invented; the offsets and the addresses are the binary's.

void Unk_1106f8a0(void** Object);
void Unk_11061eb0(void** Object);
void Unk_1106eae0(void** Object);
void Unk_1106e6d0(void** Object);

class UnkType_11067c20
{
public:
    int Unk_11067c20();

    unsigned char unk_0[0x24];
    void* unk_24;
    void* unk_28;
    void* unk_2c;
    void* unk_30;
};

// UnkType_11067c20::Unk_11067c20
int UnkType_11067c20::Unk_11067c20()
{
    if ( unk_24 != 0 )
    {
        Unk_1106f8a0(&unk_24);
    }
    if ( unk_28 != 0 )
    {
        Unk_11061eb0(&unk_28);
    }
    if ( unk_2c != 0 )
    {
        Unk_1106eae0(&unk_2c);
    }
    if ( unk_30 != 0 )
    {
        Unk_1106e6d0(&unk_30);
    }
    return 0;
}
