// campaign_leaf_465510.cpp -- thiscall at VA 0x10d65510: deletes each of the three objects the
// pointers at offsets 0, 4 and 8 point to through their virtual destructors. All names are
// invented.

class UnkType_10d65510_Obj
{
public:
    virtual ~UnkType_10d65510_Obj();
};

class UnkType_10d65510
{
public:
    void Unk_10d65510();

private:
    UnkType_10d65510_Obj* unk_00[3];
};

// UnkType_10d65510::Unk_10d65510
void UnkType_10d65510::Unk_10d65510()
{
    for (int i = 0; i < 3; i++) {
        delete unk_00[i];
    }
}
