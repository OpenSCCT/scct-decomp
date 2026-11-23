// campaign_leaf_75fca0.cpp -- one function at file offset 0x75fca0, preferred VA 0x1105fca0. When
// the count at 0x1c is below the word at 0x5c of the record at 0x8 it allocates a 0x18-byte object
// through the allocator at VA 0x10901480 and constructs it with the words at 0x14 and 0x8 and 1
// through the constructor at VA 0x110607d0, storing it at 0x0; the state at 0x18 becomes 3 when
// that fails, and otherwise 2 followed by the method at VA 0x1105fc20. With no room the state
// becomes 4. The class, method and member names are invented; the offsets and the addresses are
// the binary's.

struct UnkType_1105fca0_Record
{
    unsigned char unk_0[0x5c];
    unsigned int unk_5c;
};

class UnkType_1105fca0_Child
{
public:
    static void* operator new(unsigned int Size);

    UnkType_1105fca0_Child(int First, UnkType_1105fca0_Record* Second, int Third);

    unsigned char unk_0[0x18];
};

class UnkType_1105fca0
{
public:
    void Unk_1105fc20();
    void Unk_1105fca0();

    UnkType_1105fca0_Child* unk_0;
    int unk_4;
    UnkType_1105fca0_Record* unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
    int unk_18;
    unsigned int unk_1c;
};

// UnkType_1105fca0::Unk_1105fca0
void UnkType_1105fca0::Unk_1105fca0()
{
    if ( unk_1c < unk_8->unk_5c )
    {
        unk_0 = new UnkType_1105fca0_Child(unk_14, unk_8, 1);
        if ( unk_0 == 0 )
        {
            unk_18 = 3;
            return;
        }
        unk_18 = 2;
        Unk_1105fc20();
    }
    else
    {
        unk_18 = 4;
    }
}
