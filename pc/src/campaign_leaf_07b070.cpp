// campaign_leaf_07b070.cpp -- static function at VA 0x1097b070: constructs, in the memory its
// argument points to when that is not null, an object of the class whose vtable is at VA
// 0x110c0f50; its inline constructor runs the base constructor at VA 0x10cd7930, clears the array
// member at 0x28 and clears bit 19 of the base's flags at 0x1c. The class and member names are
// invented; the offsets, the constant and the addresses are the binary's.

inline void* operator new(unsigned int Size, void* Memory) throw()
{
    return Memory;
}

class UnkType_10cd7930_07b070
{
public:
    UnkType_10cd7930_07b070();
    virtual void VirtualSlot0();

protected:
    unsigned char unk_04[0x18];
    unsigned int unk_1c;
    unsigned char unk_20[0x08];
};

class UnkType_10cd7930_07b070_Array
{
public:
    UnkType_10cd7930_07b070_Array()
    : unk_00(0)
    , unk_04(0)
    , unk_08(0)
    {
    }

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_110c0f50 : public UnkType_10cd7930_07b070
{
public:
    UnkType_110c0f50()
    {
        unk_1c &= ~0x80000;
    }

    virtual void VirtualSlot0();
    static void Unk_1097b070(void* Memory);

private:
    UnkType_10cd7930_07b070_Array unk_28;
};

// UnkType_110c0f50::Unk_1097b070
void UnkType_110c0f50::Unk_1097b070(void* Memory)
{
    new(Memory) UnkType_110c0f50;
}
