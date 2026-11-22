// campaign_leaf_078350.cpp -- destructor of the class at VA 0x10978350, which destroys two 12-byte
// members at 0x00 and 0x0c. The class names are invented; the offsets and the member destructor's
// address (VA 0x1090ba70) are the binary's.

class UnkType_10978350_1090ba70
{
public:
    ~UnkType_10978350_1090ba70();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10978350
{
public:
    ~UnkType_10978350();

private:
    UnkType_10978350_1090ba70 unk_00;
    UnkType_10978350_1090ba70 unk_0c;
};

// UnkType_10978350::~UnkType_10978350
UnkType_10978350::~UnkType_10978350()
{
}
