// campaign_leaf_09ce80.cpp -- static function at VA 0x1099ce80 taking a block: when it is set,
// constructs an object in it with the class's inline constructor (vtable at VA 0x110c9850): runs
// the base class constructor at VA 0x10cd7930, zeroes the word at 0x28 and passes the 16 bytes at
// 0x2c, 0 and 16 to the function at VA 0x10ccad40. guess: the engine's InternalConstructor of a
// class. The class, member and function names are invented; the offsets and the addresses are the
// binary's.

void Unk_10ccad40(void* Dest, int Value, int Count);

inline void* operator new(unsigned int Size, void* Block)
{
    return Block;
}

class UnkType_1099ce80_Base
{
public:
    UnkType_1099ce80_Base();
    virtual ~UnkType_1099ce80_Base();

protected:
    unsigned char unk_04[0x28 - 0x04];
};

class UnkType_1099ce80 : public UnkType_1099ce80_Base
{
public:
    UnkType_1099ce80() : unk_28(0)
    {
        Unk_10ccad40(unk_2c, 0, sizeof(unk_2c));
    }

    virtual ~UnkType_1099ce80();

    static void Unk_1099ce80(void* Block);

private:
    int unk_28;
    unsigned char unk_2c[0x10];
};

// UnkType_1099ce80::Unk_1099ce80
void UnkType_1099ce80::Unk_1099ce80(void* Block)
{
    new(Block) UnkType_1099ce80;
}
