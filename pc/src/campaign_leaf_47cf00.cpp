// campaign_leaf_47cf00.cpp -- thiscall at VA 0x10d7cf00: calls the free function at VA 0x10d7ce40
// with the object and its argument, and returns the object. All names are invented.

class UnkType_10d7cf00;

void Unk_10d7ce40(UnkType_10d7cf00* Object, int Value);

class UnkType_10d7cf00
{
public:
    UnkType_10d7cf00& Unk_10d7cf00(int Value);
};

// UnkType_10d7cf00::Unk_10d7cf00
UnkType_10d7cf00& UnkType_10d7cf00::Unk_10d7cf00(int Value)
{
    Unk_10d7ce40(this, Value);
    return *this;
}
