// campaign_leaf_2f7be0.cpp -- destructor of the class at VA 0x10bf7be0: it calls the base-class
// member at VA 0x10cd7a30; then the string member at 0x3fc is destroyed (destructor at VA
// 0x1090ba70) and the base destructor at VA 0x10bee4f0 runs. The class names are invented; the
// offsets and addresses are the binary's.

class UnkType_1090ba70
{
public:
    ~UnkType_1090ba70();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10bee4f0
{
public:
    virtual ~UnkType_10bee4f0();
    void Unk_10cd7a30();

private:
    unsigned char unk_004[0x3fc - 4];
};

class UnkType_10bf7be0 : public UnkType_10bee4f0
{
public:
    virtual ~UnkType_10bf7be0();

private:
    UnkType_1090ba70 unk_3fc;
};

// UnkType_10bf7be0::~UnkType_10bf7be0
UnkType_10bf7be0::~UnkType_10bf7be0()
{
    Unk_10cd7a30();
}
