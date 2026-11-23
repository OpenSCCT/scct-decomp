// campaign_leaf_4902a0.cpp -- thiscall method at VA 0x10d902a0, from Core/SystemComponents.h (the
// wide file name and line 47 it passes to the allocating operator new). It creates a 0x28-byte
// object named L"Session" (constructor at 0x10dc3120, taking a temporary string built by
// 0x10d7cf00 and destroyed by 0x10d7cf40), stores it at 0x2c and passes it to its own method at
// 0x10dc3280. The class, method and member names are invented.

void* operator new(unsigned int Size, const unsigned short* File, int Line);

class UnkType_10d902a0_String
{
public:
    UnkType_10d902a0_String(const unsigned short* Text);
    ~UnkType_10d902a0_String();

private:
    unsigned short* unk_0;
};

class UnkType_10d902a0_Component
{
public:
    UnkType_10d902a0_Component(const UnkType_10d902a0_String& Name);

private:
    unsigned char unk_0[0x28];
};

class UnkType_10d902a0
{
public:
    void Unk_10d902a0();
    void Unk_10dc3280(UnkType_10d902a0_Component* Component);

private:
    unsigned char unk_0[0x2c];
    UnkType_10d902a0_Component* unk_2c;
};

// UnkType_10d902a0::Unk_10d902a0
void UnkType_10d902a0::Unk_10d902a0()
{
    unk_2c = new(L"../../.././src\\Core/SystemComponents.h", 0x2f)
        UnkType_10d902a0_Component(L"Session");
    Unk_10dc3280(unk_2c);
}
