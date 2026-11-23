// campaign_leaf_484280.cpp -- destructor at VA 0x10d84280. It resets the reference at 0x08 by
// assigning it a temporary reference built from key 0 (constructor at 0x10d8ef70, assignment at
// 0x10d8ef20, destructor at 0x10d8edb0); the members at 0x30, 0x18 (destructor at 0x10d9a410) and
// 0x08 are then destroyed. The class and member names are invented.

struct UnkType_10d84280_Key
{
    UnkType_10d84280_Key(unsigned int Value) : unk_0(Value) {}
    UnkType_10d84280_Key(const UnkType_10d84280_Key& Other) : unk_0(Other.unk_0) {}

    unsigned int unk_0;
};

class UnkType_10d84280_Ref
{
public:
    UnkType_10d84280_Ref(UnkType_10d84280_Key Key);
    ~UnkType_10d84280_Ref();
    UnkType_10d84280_Ref& operator=(const UnkType_10d84280_Ref& Other);

private:
    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10d84280_Table
{
public:
    ~UnkType_10d84280_Table();

private:
    unsigned char unk_0[0x18];
};

class UnkType_10d84280
{
public:
    virtual ~UnkType_10d84280();

private:
    int unk_4;
    UnkType_10d84280_Ref unk_8;
    int unk_14;
    UnkType_10d84280_Table unk_18;
    UnkType_10d84280_Table unk_30;
};

// UnkType_10d84280::~UnkType_10d84280
UnkType_10d84280::~UnkType_10d84280()
{
    unk_8 = UnkType_10d84280_Key(0);
}
