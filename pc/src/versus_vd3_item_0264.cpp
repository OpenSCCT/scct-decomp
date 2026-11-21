// Unnamed classes: no vtable label or string evidence for names here.
// UnnamedClass_62850 holds a pointer to a large owner object at +0x108 and a
// pointer to a four-dword record at +0x2af10. The owner holds an interface
// pointer at +0x46a4 whose vtable slot 31 (+0x7c) is a COM-style __stdcall method taking two ints.

class UnnamedInterface_62850
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25(); virtual void Slot26(); virtual void Slot27();
    virtual void Slot28(); virtual void Slot29(); virtual void Slot30();
    virtual void __stdcall SetSize(int X, int Y);   // COM-style: this pushed on the stack
};

struct UnnamedOwner_62850
{
    unsigned char Pad0[0x46a4];
    UnnamedInterface_62850 *Interface;   // +0x46a4
    unsigned char Pad1[0x30e20 - 0x46a8];
    int SizeY;                           // +0x30e20
    int Pad2;
    int SizeX;                           // +0x30e28
};

struct UnnamedRecord_62850
{
    int X;
    int Y;
    int A;
    int B;
};

class UnnamedClass_62850
{
public:
    unsigned char Pad0[0x108];
    UnnamedOwner_62850 *Owner;           // +0x108
    unsigned char Pad1[0x2af10 - 0x10c];
    UnnamedRecord_62850 *Record;         // +0x2af10

    void Update();
};

void UnnamedClass_62850::Update()
{
    Owner->Interface->SetSize(Owner->SizeX, Owner->SizeY);
    Record->X = Owner->SizeX;
    Record->Y = Owner->SizeY;
    Record->A = 0;
    Record->B = 0;
}
