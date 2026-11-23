// campaign_leaf_76ac40.cpp -- thiscall method at VA 0x1106ac40: calls the method at VA 0x1105eef0
// on the object at 0x68, then the method at VA 0x11067db0 on the object at 0x70. All names are
// invented.

class UnkType_1105eef0
{
public:
    void Unk_1105eef0();
};

class UnkType_11067db0
{
public:
    void Unk_11067db0();
};

class UnkType_1106ac40
{
public:
    void Unk_1106ac40();

private:
    int unk_00[26];
    UnkType_1105eef0* unk_68;
    int unk_6c;
    UnkType_11067db0* unk_70;
};

// UnkType_1106ac40::Unk_1106ac40
void UnkType_1106ac40::Unk_1106ac40()
{
    unk_68->Unk_1105eef0();
    unk_70->Unk_11067db0();
}
