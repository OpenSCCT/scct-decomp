// campaign_leaf_1ae640.cpp -- method at VA 0x10aae640 taking two unused arguments: returns, by
// value, an object built from the empty wide string by the constructor at VA 0x1090ba00. It does
// not use this. The class and method names are invented; the address is the binary's.

class UnkType_10aae640_1090ba00
{
public:
    UnkType_10aae640_1090ba00(const unsigned short* Text);
    ~UnkType_10aae640_1090ba00();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10aae640
{
public:
    UnkType_10aae640_1090ba00 Unk_10aae640(int Arg0, int Arg1);
};

// UnkType_10aae640::Unk_10aae640
UnkType_10aae640_1090ba00 UnkType_10aae640::Unk_10aae640(int Arg0, int Arg1)
{
    return UnkType_10aae640_1090ba00(L"");
}
