// campaign_leaf_610870.cpp -- thiscall method at VA 0x10f10870: deletes the object at 0x04 through
// its virtual destructor and clears the pointer. The class and method names are invented.

class UnkType_10f10870_04
{
public:
    virtual ~UnkType_10f10870_04();
};

class UnkType_10f10870
{
public:
    void Unk_10f10870();

private:
    int unk_00;
    UnkType_10f10870_04* unk_04;
};

// UnkType_10f10870::Unk_10f10870
void UnkType_10f10870::Unk_10f10870()
{
    delete unk_04;
    unk_04 = 0;
}
