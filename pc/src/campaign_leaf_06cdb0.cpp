// campaign_leaf_06cdb0.cpp -- static function at VA 0x1096cdb0: constructs, in the memory its
// argument points to when that is not null, an object of the class whose vtable is at VA
// 0x110c06c0; its inline constructor runs the inline constructor of its base class, which runs the
// base constructor at VA 0x10cd7930, clears the value at 0x64 and sets the one at 0x68 to -1. The
// class and member names are invented; the offsets, the constants and the addresses are the
// binary's.

inline void* operator new(unsigned int Size, void* Memory) throw()
{
    return Memory;
}

class UnkType_10cd7930_06cdb0
{
public:
    UnkType_10cd7930_06cdb0();
    virtual void VirtualSlot0();

private:
    unsigned char unk_04[0x60];
};

class UnkType_110bf470 : public UnkType_10cd7930_06cdb0
{
public:
    UnkType_110bf470()
    : unk_64(0)
    , unk_68(-1)
    {
    }

    virtual void VirtualSlot0();

private:
    int unk_64;
    int unk_68;
};

class UnkType_110c06c0 : public UnkType_110bf470
{
public:
    UnkType_110c06c0()
    {
    }

    virtual void VirtualSlot0();
    static void Unk_1096cdb0(void* Memory);
};

// UnkType_110c06c0::Unk_1096cdb0
void UnkType_110c06c0::Unk_1096cdb0(void* Memory)
{
    new(Memory) UnkType_110c06c0;
}
