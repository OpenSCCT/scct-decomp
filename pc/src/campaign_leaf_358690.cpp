// campaign_leaf_358690.cpp -- a member function at VA 0x10c58690 that passes its argument to the
// member at VA 0x10bee050 and then, when the argument is not zero, calls the member at VA
// 0x10a81ff0 with 0x45. The class, method and parameter names are invented; the addresses and
// constant are the binary's.

class UnkType_10c58690
{
public:
    void Unk_10bee050(int Value);
    void Unk_10a81ff0(int Value);
    void Unk_10c58690(int Value);
};

// UnkType_10c58690::Unk_10c58690
void UnkType_10c58690::Unk_10c58690(int Value)
{
    Unk_10bee050(Value);
    if ( Value )
    {
        Unk_10a81ff0(0x45);
    }
}
