// campaign_leaf_0098c0.cpp -- constructor at VA 0x109098c0: stores its argument at 0x00 and -1 at
// 0x04, then calls the method at VA 0x10908050. The class and method names are invented; the
// offsets, the constant and the address are the binary's.

class UnkType_109098c0
{
public:
    UnkType_109098c0(int Value);
    void Unk_10908050();

private:
    int unk_00;
    int unk_04;
};

// UnkType_109098c0::UnkType_109098c0
UnkType_109098c0::UnkType_109098c0(int Value)
: unk_00(Value)
, unk_04(-1)
{
    Unk_10908050();
}
