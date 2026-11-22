// campaign_leaf_338980.cpp -- a member function at VA 0x10c38980 that calls two other members on
// the same object, at VA 0x10c38480 and VA 0x10c37470. The class and method names are invented;
// the addresses are the binary's.

class UnkType_10c38980
{
public:
    void Unk_10c38480();
    void Unk_10c37470();
    void Unk_10c38980();
};

// UnkType_10c38980::Unk_10c38980
void UnkType_10c38980::Unk_10c38980()
{
    Unk_10c38480();
    Unk_10c37470();
}
