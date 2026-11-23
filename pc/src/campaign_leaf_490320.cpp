// campaign_leaf_490320.cpp -- thiscall method at VA 0x10d90320, from Core/SystemComponents.h (the
// wide file name and line 48 it passes to the allocating operator new). It creates a 0x28-byte
// object named L"DOCore" (constructor at 0x10dc3120, taking a temporary string built by
// 0x10d7cf00 and destroyed by 0x10d7cf40), stores it at 0x30 and passes it to its own method at
// 0x10dc3280. The class, method and member names are invented.

void* operator new(unsigned int Size, const unsigned short* File, int Line);

class UnkType_10d90320_String
{
public:
    UnkType_10d90320_String(const unsigned short* Text);
    ~UnkType_10d90320_String();

private:
    unsigned short* unk_0;
};

class UnkType_10d90320_Component
{
public:
    UnkType_10d90320_Component(const UnkType_10d90320_String& Name);

private:
    unsigned char unk_0[0x28];
};

class UnkType_10d90320
{
public:
    void Unk_10d90320();
    void Unk_10dc3280(UnkType_10d90320_Component* Component);

private:
    unsigned char unk_0[0x30];
    UnkType_10d90320_Component* unk_30;
};

// UnkType_10d90320::Unk_10d90320
void UnkType_10d90320::Unk_10d90320()
{
    unk_30 = new(L"../../.././src\\Core/SystemComponents.h", 0x30)
        UnkType_10d90320_Component(L"DOCore");
    Unk_10dc3280(unk_30);
}
