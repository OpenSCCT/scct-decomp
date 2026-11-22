// campaign_leaf_45f720.cpp -- thiscall at VA 0x10d5f720: converts its int argument to float and
// passes it to the method at VA 0x10d5f5f0 on the same object. Class and method names are
// invented.

class UnkType_10d5f720
{
public:
    void Unk_10d5f5f0(float Value);
    void Unk_10d5f720(int Value);
};

// UnkType_10d5f720::Unk_10d5f720
void UnkType_10d5f720::Unk_10d5f720(int Value)
{
    Unk_10d5f5f0((float)Value);
}
