// campaign_leaf_03a070.cpp -- method at VA 0x1093a070: passes its argument to the method at VA
// 0x10936110 on the same object and returns the object. The class and method names are invented;
// the addresses are the binary's.

class UnkType_1093a070
{
public:
    UnkType_1093a070& Unk_1093a070(int Value);
    void Unk_10936110(int Value);
};

// UnkType_1093a070::Unk_1093a070
UnkType_1093a070& UnkType_1093a070::Unk_1093a070(int Value)
{
    Unk_10936110(Value);
    return *this;
}
