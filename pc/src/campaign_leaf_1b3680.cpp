// campaign_leaf_1b3680.cpp -- constructor at VA 0x10ab3680 taking a value for the base class
// constructor at VA 0x10abd8f0, an actor and a word. It installs the class's vtable (VA
// 0x110da26c), keeps the word at 0x23c, asks the object at 0x220 (method at VA 0x10a99ad0, given
// the actor's word at 0x78 and its position at 0xe8) for a 12-byte result, and keeps the actor at
// 0x224, its position at 0x1cc and the result's byte at 0x08 at 0x228. The class, method and member
// names are invented.

class UnkType_10ab3680_Vector
{
public:
    float X;
    float Y;
    float Z;
};

struct UnkType_10ab3680_Result
{
    int unk_0;
    int unk_4;
    unsigned char unk_8;
};

struct UnkType_10ab3680_Actor
{
    char unk_00[0x78];
    int unk_78;
    char unk_7c[0xe8 - 0x7c];
    UnkType_10ab3680_Vector unk_e8;
};

class UnkType_10ab3680_Query
{
public:
    UnkType_10ab3680_Result Unk_10a99ad0(int Value, UnkType_10ab3680_Vector Location);
};

class UnkType_10ab3680_Base
{
public:
    UnkType_10ab3680_Base(int Value);

    virtual void VirtualSlot0();

private:
    char unk_004[0x1cc - 0x004];
};

class UnkType_10ab3680 : public UnkType_10ab3680_Base
{
public:
    UnkType_10ab3680(int Value, UnkType_10ab3680_Actor* Actor, int Word);

    virtual void VirtualSlot0();

private:
    UnkType_10ab3680_Vector unk_1cc;
    char unk_1d8[0x220 - 0x1d8];
    UnkType_10ab3680_Query* unk_220;
    UnkType_10ab3680_Actor* unk_224;
    int unk_228;
    char unk_22c[0x23c - 0x22c];
    int unk_23c;
};

// UnkType_10ab3680::UnkType_10ab3680
UnkType_10ab3680::UnkType_10ab3680(int Value, UnkType_10ab3680_Actor* Actor, int Word)
    : UnkType_10ab3680_Base(Value)
{
    unk_23c = Word;
    UnkType_10ab3680_Result Result = unk_220->Unk_10a99ad0(Actor->unk_78, Actor->unk_e8);
    unk_224 = Actor;
    unk_1cc = Actor->unk_e8;
    unk_228 = Result.unk_8;
}
