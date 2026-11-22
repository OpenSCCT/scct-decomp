// campaign_leaf_47cee0.cpp -- thiscall at VA 0x10d7cee0: calls the free function at VA 0x10d7cd80
// with the object and its argument, and returns the object. All names are invented.

class UnkType_10d7cee0;

void Unk_10d7cd80(UnkType_10d7cee0* Object, int Value);

class UnkType_10d7cee0
{
public:
    UnkType_10d7cee0& Unk_10d7cee0(int Value);
};

// UnkType_10d7cee0::Unk_10d7cee0
UnkType_10d7cee0& UnkType_10d7cee0::Unk_10d7cee0(int Value)
{
    Unk_10d7cd80(this, Value);
    return *this;
}
