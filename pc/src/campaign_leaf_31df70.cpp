// campaign_leaf_31df70.cpp -- a member function at VA 0x10c1df70 that returns, by value, a copy
// (constructor at VA 0x10c1db40) of the member at 0x9ac. The class, method and member names are
// invented; the offsets and addresses are the binary's.

class UnkType_10c1db40
{
public:
    UnkType_10c1db40(const UnkType_10c1db40& Other);
};

class UnkType_10c1df70
{
public:
    UnkType_10c1db40 Unk_10c1df70();

private:
    unsigned char unk_000[0x9ac];
    UnkType_10c1db40 unk_9ac;
};

// UnkType_10c1df70::Unk_10c1df70
UnkType_10c1db40 UnkType_10c1df70::Unk_10c1df70()
{
    return unk_9ac;
}
