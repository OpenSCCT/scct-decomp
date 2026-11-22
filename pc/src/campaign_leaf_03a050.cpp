// campaign_leaf_03a050.cpp -- method at VA 0x1093a050: passes its argument to the method at VA
// 0x10936060 on the same object and returns the object. The class and method names are invented;
// the addresses are the binary's.

class UnkType_1093a050
{
public:
    UnkType_1093a050& Unk_1093a050(int Value);
    void Unk_10936060(int Value);
};

// UnkType_1093a050::Unk_1093a050
UnkType_1093a050& UnkType_1093a050::Unk_1093a050(int Value)
{
    Unk_10936060(Value);
    return *this;
}
