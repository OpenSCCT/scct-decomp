// campaign_leaf_502740.cpp -- constructor at VA 0x10e02740: its base sets the count at 0x06 to 1;
// clears 0x08 and 0x10, stores the buffer at 0x0c and the limit at 0x14 (one less than the size
// when the buffer is to be cleared), clears the byte at 0x18, and clears the buffer through the
// function at VA 0x10dffeb0 when asked. The class, member and parameter names are invented; the
// offsets, the vtable and the address are the binary's.

void* Unk_10dffeb0(void* Data, int Value, int Size);

class UnkType_10e02740_Counted
{
public:
    UnkType_10e02740_Counted()
        : unk_06(1)
    {
    }
    virtual ~UnkType_10e02740_Counted();

    unsigned short unk_04;
    unsigned short unk_06;
};

class UnkType_10e02740 : public UnkType_10e02740_Counted
{
public:
    UnkType_10e02740(char* Data, int Size, bool Clear);
    virtual ~UnkType_10e02740();

    int unk_08;
    char* unk_0c;
    int unk_10;
    int unk_14;
    bool unk_18;
};

// UnkType_10e02740::UnkType_10e02740
UnkType_10e02740::UnkType_10e02740(char* Data, int Size, bool Clear)
{
    unk_08 = 0;
    unk_0c = Data;
    unk_10 = 0;
    unk_14 = Clear ? Size - 1 : Size;
    unk_18 = false;
    if ( Clear )
    {
        Unk_10dffeb0(Data, 0, Size);
    }
}
