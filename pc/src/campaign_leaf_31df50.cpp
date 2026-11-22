// campaign_leaf_31df50.cpp -- a member function at VA 0x10c1df50 that passes a reference to its
// argument to the member at VA 0x10c1def0 of the object at 0x9ac. The class, method and member
// names are invented; the offsets and addresses are the binary's.

class UnkType_10c1def0
{
public:
    void Unk_10c1def0(const int& Value);
};

class UnkType_10c1df50
{
public:
    void Unk_10c1df50(int Value);

private:
    unsigned char unk_000[0x9ac];
    UnkType_10c1def0 unk_9ac;
};

// UnkType_10c1df50::Unk_10c1df50
void UnkType_10c1df50::Unk_10c1df50(int Value)
{
    unk_9ac.Unk_10c1def0(Value);
}
