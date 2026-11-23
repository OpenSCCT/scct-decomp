// campaign_leaf_4e7d70.cpp -- one function at file offset 0x4e7d70, preferred VA 0x10de7d70.
// It returns the result of the method at 0x10de6fb0 of the object that the method at 0x10dce7f0
// of the object at offset 4 returns for Value. The class, method and member names are invented;
// the offset and the bytes are the binary's.

class UnkType_10de7d70_Result
{
public:
    int Unk_10de6fb0();
};

class UnkType_10de7d70_Inner
{
public:
    UnkType_10de7d70_Result* Unk_10dce7f0(int Value);
};

class UnkType_10de7d70
{
public:
    int unk_0;
    UnkType_10de7d70_Inner* unk_4;

    int Unk_10de7d70(int Value);
};

// UnkType_10de7d70::Unk_10de7d70
int UnkType_10de7d70::Unk_10de7d70(int Value)
{
    return unk_4->Unk_10dce7f0(Value)->Unk_10de6fb0();
}
