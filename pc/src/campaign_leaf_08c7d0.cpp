// campaign_leaf_08c7d0.cpp -- method at VA 0x1098c7d0: passes its argument by reference to the
// method at VA 0x1098c560 of the member at 0x44. The class, member and method names are invented;
// the offsets and the addresses are the binary's.

class UnkType_1098c7d0_1098c560
{
public:
    void Unk_1098c560(const int& Value);
};

class UnkType_1098c7d0
{
public:
    void Unk_1098c7d0(int Value);

private:
    unsigned char unk_00[0x44];
    UnkType_1098c7d0_1098c560 unk_44;
};

// UnkType_1098c7d0::Unk_1098c7d0
void UnkType_1098c7d0::Unk_1098c7d0(int Value)
{
    unk_44.Unk_1098c560(Value);
}
