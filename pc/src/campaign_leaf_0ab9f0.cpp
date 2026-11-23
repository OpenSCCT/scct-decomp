// campaign_leaf_0ab9f0.cpp -- static function at VA 0x109ab9f0 taking a block: when it is set,
// constructs an object in it with the class's inline constructor (vtable at VA 0x110ccb80): runs
// the base class constructor at VA 0x10cd7930, then zeroes the words at 0x28, 0x38, 0x3c, 0x40 and
// 0x44. guess: the engine's InternalConstructor of a class. The class and member names are
// invented; the offsets and the addresses are the binary's.

inline void* operator new(unsigned int Size, void* Block)
{
    return Block;
}

class UnkType_109ab9f0_Base
{
public:
    UnkType_109ab9f0_Base();
    virtual ~UnkType_109ab9f0_Base();

protected:
    unsigned char unk_04[0x28 - 0x04];
};

class UnkType_109ab9f0 : public UnkType_109ab9f0_Base
{
public:
    UnkType_109ab9f0() : unk_28(0), unk_38(0), unk_3c(0), unk_40(0), unk_44(0)
    {
    }
    virtual ~UnkType_109ab9f0();

    static void Unk_109ab9f0(void* Block);

private:
    int unk_28;
    unsigned char unk_2c[0x38 - 0x2c];
    int unk_38;
    int unk_3c;
    int unk_40;
    int unk_44;
};

// UnkType_109ab9f0::Unk_109ab9f0
void UnkType_109ab9f0::Unk_109ab9f0(void* Block)
{
    new(Block) UnkType_109ab9f0;
}
