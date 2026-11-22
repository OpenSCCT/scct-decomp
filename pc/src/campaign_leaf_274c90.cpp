// campaign_leaf_274c90.cpp -- a member function at VA 0x10b74c90 that looks up an object with the
// member at VA 0x10a0e220, given the byte at 0x0c of the object the pointer at 0x10 refers to and
// called on that object's pointer at 0x04, and returns whether the member at VA 0x10a45b50 of the
// result's object at 0x64 returns non-zero. The class, method and member names are invented; the
// offsets and addresses are the binary's.

class UnkType_10a45b50
{
public:
    int Unk_10a45b50();
};

class UnkType_10a0e220_Result
{
public:
    unsigned char unk_00[0x64];
    UnkType_10a45b50* unk_64;
};

class UnkType_10a0e220
{
public:
    UnkType_10a0e220_Result* Unk_10a0e220(unsigned char Index);
};

class UnkType_10b74c90_Item
{
public:
    int unk_00;
    UnkType_10a0e220* unk_04;
    int unk_08;
    unsigned char unk_0c;
};

class UnkType_10b74c90
{
public:
    bool Unk_10b74c90();

private:
    unsigned char unk_00[0x10];
    UnkType_10b74c90_Item* unk_10;
};

// UnkType_10b74c90::Unk_10b74c90
bool UnkType_10b74c90::Unk_10b74c90()
{
    return unk_10->unk_04->Unk_10a0e220(unk_10->unk_0c)->unk_64->Unk_10a45b50() ? true : false;
}
