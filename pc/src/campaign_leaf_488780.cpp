// campaign_leaf_488780.cpp -- constructor at VA 0x10d88780 of a polymorphic class whose vtable is at
// VA 0x1113cc18; runs the base constructor at VA 0x10dbd740 and stores its unsigned char argument at
// offset 8. All names are invented.

class UnkType_10dbd740
{
public:
    UnkType_10dbd740();
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10d88780 : public UnkType_10dbd740
{
public:
    UnkType_10d88780(unsigned char Value);
    virtual void VirtualSlot0();

private:
    unsigned char unk_08;
};

// UnkType_10d88780::UnkType_10d88780
UnkType_10d88780::UnkType_10d88780(unsigned char Value) : unk_08(Value)
{
}
