// campaign_leaf_0961f0.cpp -- static function at VA 0x109961f0 taking a block: when it is set,
// constructs an object in it with the class's inline constructor (vtable at VA 0x110c71d8): the
// base class constructor at VA 0x10cd7930, then the 16-byte record at 0x1cc zeroed except its float
// at 0x1d4, set to 1e-8. guess: the engine's InternalConstructor of a class. The class and member
// names are invented; the offsets, the values and the addresses are the binary's.

inline void* operator new(unsigned int Size, void* Block)
{
    return Block;
}

class UnkType_109961f0_Base
{
public:
    UnkType_109961f0_Base();
    virtual ~UnkType_109961f0_Base();

private:
    unsigned char unk_04[0x1cc - 0x04];
};

struct UnkType_109961f0_Sub
{
    UnkType_109961f0_Sub() : unk_00(0), unk_04(0), unk_08(1e-8f), unk_0c(0)
    {
    }

    int unk_00;
    int unk_04;
    float unk_08;
    int unk_0c;
};

class UnkType_109961f0_Middle : public UnkType_109961f0_Base
{
public:
    virtual ~UnkType_109961f0_Middle();

private:
    UnkType_109961f0_Sub unk_1cc;
};

class UnkType_109961f0 : public UnkType_109961f0_Middle
{
public:
    UnkType_109961f0()
    {
    }

    virtual ~UnkType_109961f0();

    static void Unk_109961f0(void* Block);
};

// UnkType_109961f0::Unk_109961f0
void UnkType_109961f0::Unk_109961f0(void* Block)
{
    new(Block) UnkType_109961f0;
}
