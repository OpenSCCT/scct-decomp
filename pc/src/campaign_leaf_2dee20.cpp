// campaign_leaf_2dee20.cpp -- a member function at VA 0x10bdee20 that passes a reference to its
// argument to the member at VA 0x10bdc8e0 of the object at 0x2f0. The class, method and member
// names are invented; the offsets and addresses are the binary's.

class UnkType_10bdc8e0
{
public:
    void Unk_10bdc8e0(const int& Value);
};

class UnkType_10bdee20
{
public:
    void Unk_10bdee20(int Value);

private:
    unsigned char unk_000[0x2f0];
    UnkType_10bdc8e0 unk_2f0;
};

// UnkType_10bdee20::Unk_10bdee20
void UnkType_10bdee20::Unk_10bdee20(int Value)
{
    unk_2f0.Unk_10bdc8e0(Value);
}
