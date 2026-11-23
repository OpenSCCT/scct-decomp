// campaign_leaf_47e050.cpp -- thiscall method at VA 0x10d7e050. It assigns (0x10d8ef20) its
// reference at 0x8c a temporary reference built from the key 0 (constructor at 0x10d8ef70,
// destructor at 0x10d8edb0). The class and method names are invented.

struct UnkType_10d7e050_Key
{
    UnkType_10d7e050_Key(unsigned int Value) : unk_0(Value) {}
    UnkType_10d7e050_Key(const UnkType_10d7e050_Key& Other) : unk_0(Other.unk_0) {}

    unsigned int unk_0;
};

class UnkType_10d7e050_Ref
{
public:
    UnkType_10d7e050_Ref(UnkType_10d7e050_Key Key);
    ~UnkType_10d7e050_Ref();
    UnkType_10d7e050_Ref& operator=(const UnkType_10d7e050_Ref& Other);

private:
    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10d7e050
{
public:
    void Unk_10d7e050();

private:
    unsigned char unk_0[0x8c];
    UnkType_10d7e050_Ref unk_8c;
};

// UnkType_10d7e050::Unk_10d7e050
void UnkType_10d7e050::Unk_10d7e050()
{
    unk_8c = UnkType_10d7e050_Key(0);
}
