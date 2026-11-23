// campaign_leaf_76c490.cpp -- one function at file offset 0x76c490, preferred VA 0x1106c490. When
// the object at 0x64 is set it passes that member's address to the function at VA 0x11070cf0
// (which deletes the object and clears the pointer); it then stores its second argument at 0x4
// and calls the method at VA 0x1106c400. The first argument is not read. The class, method and
// member names are invented; the offsets and the addresses are the binary's.

void Unk_11070cf0(void** Object);

class UnkType_1106c490
{
public:
    void Unk_1106c400();
    void Unk_1106c490(int First, int Second);

    int unk_0;
    int unk_4;
    unsigned char unk_8[0x64 - 0x8];
    void* unk_64;
};

// UnkType_1106c490::Unk_1106c490
void UnkType_1106c490::Unk_1106c490(int First, int Second)
{
    if ( unk_64 != 0 )
    {
        Unk_11070cf0(&unk_64);
    }
    unk_4 = Second;
    Unk_1106c400();
}
