// campaign_leaf_610960.cpp -- thiscall method at VA 0x10f10960: when the pointer at 0x04 is set,
// deletes that object through its virtual destructor and clears the pointer; returns true. The
// class and method names are invented.

class UnkType_10f10960_04
{
public:
    virtual ~UnkType_10f10960_04();
};

class UnkType_10f10960
{
public:
    bool Unk_10f10960();

private:
    int unk_00;
    UnkType_10f10960_04* unk_04;
};

// UnkType_10f10960::Unk_10f10960
bool UnkType_10f10960::Unk_10f10960()
{
    if ( unk_04 )
    {
        delete unk_04;
        unk_04 = 0;
    }
    return true;
}
