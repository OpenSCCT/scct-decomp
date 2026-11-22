// campaign_leaf_3ca830.cpp -- a member function at VA 0x10cca830 that returns, by value, a string
// built from the empty wide string (constructor at VA 0x1090ba00). The destructor at VA 0x1090ba70
// names the string class. It does not read this. The class and method names are invented; the
// addresses are the binary's.

class UnkType_1090ba00
{
public:
    UnkType_1090ba00(const unsigned short* Text);
    UnkType_1090ba00(const UnkType_1090ba00& Other);
    ~UnkType_1090ba00();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10cca830
{
public:
    UnkType_1090ba00 Unk_10cca830();
};

// UnkType_10cca830::Unk_10cca830
UnkType_1090ba00 UnkType_10cca830::Unk_10cca830()
{
    return L"";
}
