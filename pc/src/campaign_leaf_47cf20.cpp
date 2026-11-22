// campaign_leaf_47cf20.cpp -- thiscall at VA 0x10d7cf20: calls the free function at VA 0x10d7ce40
// with the object and the dword its argument refers to, and returns the object. All names are
// invented.

class UnkType_10d7cf20;

void Unk_10d7ce40(UnkType_10d7cf20* Object, int Value);

class UnkType_10d7cf20
{
public:
    UnkType_10d7cf20& Unk_10d7cf20(const int& Value);
};

// UnkType_10d7cf20::Unk_10d7cf20
UnkType_10d7cf20& UnkType_10d7cf20::Unk_10d7cf20(const int& Value)
{
    Unk_10d7ce40(this, Value);
    return *this;
}
