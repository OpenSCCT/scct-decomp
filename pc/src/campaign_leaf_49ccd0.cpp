// campaign_leaf_49ccd0.cpp -- thiscall method at VA 0x10d9ccd0. When its method at 0x10d95310
// refuses, it reports the code 0xe000000e through 0x10d977f0 and returns false. Otherwise it
// passes 0 and 0 to its part at 0xa4 (0x10d9cad0), stores the given key in its part at 0x70
// (0x10d8eee0) and the given 16-bit value at 0xa0, deletes its object at 0x9c (destructor at
// 0x10d9d610) and replaces it with the one returned by the method at 0x10da8bd0 of the result of
// 0x10da9120 for this object, and returns true. The class, method and parameter names are
// invented.

struct UnkType_10d9ccd0_Key
{
    int unk_0;
};

class UnkType_10d9ccd0_Object
{
public:
    ~UnkType_10d9ccd0_Object();
};

class UnkType_10d9ccd0_Factory
{
public:
    UnkType_10d9ccd0_Object* Unk_10da8bd0();
};

class UnkType_10d9ccd0_KeyPart
{
public:
    void Unk_10d8eee0(const UnkType_10d9ccd0_Key& Key);

private:
    int unk_0;
};

class UnkType_10d9ccd0_List
{
public:
    void Unk_10d9cad0(int First, int Second);

private:
    int unk_0;
};

class UnkType_10d9ccd0;

void Unk_10d977f0(int First, int Second, unsigned int Code, int Fourth);
UnkType_10d9ccd0_Factory* __stdcall Unk_10da9120(UnkType_10d9ccd0* Owner);

class UnkType_10d9ccd0
{
public:
    bool Unk_10d9ccd0(UnkType_10d9ccd0_Key Key, unsigned short Value);
    bool Unk_10d95310();

private:
    unsigned char unk_0[0x70];
    UnkType_10d9ccd0_KeyPart unk_70;
    unsigned char unk_74[0x28];
    UnkType_10d9ccd0_Object* unk_9c;
    unsigned short unk_a0;
    UnkType_10d9ccd0_List unk_a4;
};

// UnkType_10d9ccd0::Unk_10d9ccd0
bool UnkType_10d9ccd0::Unk_10d9ccd0(UnkType_10d9ccd0_Key Key, unsigned short Value)
{
    if ( !Unk_10d95310() )
    {
        Unk_10d977f0(0, 0, 0xe000000e, 0);
        return false;
    }
    unk_a4.Unk_10d9cad0(0, 0);
    unk_70.Unk_10d8eee0(Key);
    unk_a0 = Value;
    if ( unk_9c != 0 )
    {
        delete unk_9c;
        unk_9c = 0;
    }
    unk_9c = Unk_10da9120(this)->Unk_10da8bd0();
    return true;
}
