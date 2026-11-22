// campaign_leaf_1b0b10.cpp -- destructor of the class at VA 0x10ab0b10: destroys the 12-byte member
// at 0x64 with the destructor at VA 0x1090ba70, then runs the base class destructor at VA
// 0x1097c520. The class names are invented; the offsets and the addresses are the binary's.

class UnkType_1090ba70
{
public:
    ~UnkType_1090ba70();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1097c520
{
public:
    ~UnkType_1097c520();

private:
    unsigned char unk_00[0x64];
};

class UnkType_10ab0b10 : public UnkType_1097c520
{
public:
    ~UnkType_10ab0b10();

private:
    UnkType_1090ba70 unk_64;
};

// UnkType_10ab0b10::~UnkType_10ab0b10
UnkType_10ab0b10::~UnkType_10ab0b10()
{
}
