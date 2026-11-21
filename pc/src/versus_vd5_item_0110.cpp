// Work item 0110: RVA 0xb4750, an inlined-to-LTCG constructor (this in EAX).
// Class identity unknown: neutral name UnnamedClass_b4750. Vtable at 0x10c049e4.
// Fields 0x04-0x18 and 0x34 are left untouched by the constructor.
typedef int INT;

class UnnamedClass_b4750
{
public:
    UnnamedClass_b4750();
    virtual void VFunc0();

    INT Unk04[6];       // 0x04-0x18, not initialised here
    INT Unk1C;
    INT Unk20;
    INT Unk24;
    INT Unk28;
    INT Unk2C;
    INT Unk30;
    INT Unk34;          // not initialised here
    INT Unk38;
    INT Unk3C;
    INT Unk40;
    INT Unk44;
    INT Unk48;
    INT Unk4C;
    INT Unk50;
    INT Unk54;
    INT Unk58;
    INT Unk5C;
    INT Unk60;
    INT Unk64;
};

UnnamedClass_b4750::UnnamedClass_b4750()
{
    Unk1C = 0;
    Unk20 = 0;
    Unk24 = 0;
    Unk28 = 0;
    Unk2C = 0;
    Unk30 = 0;
    Unk38 = 0;
    Unk3C = 0;
    Unk40 = 0;
    Unk44 = 0;
    Unk48 = 0;
    Unk4C = 0;
    Unk50 = 0;
    Unk54 = 0;
    Unk58 = 0;
    Unk5C = 0;
    Unk60 = 0;
    Unk64 = 0;
}

// Scaffolding for the link, not part of the unit.
void *operator new(unsigned int, void *P);
inline void *operator new(unsigned int, void *P) { return P; }
void Driver_b4750(void *A, void *B, void *C) { new(A) UnnamedClass_b4750; new(B) UnnamedClass_b4750; new(C) UnnamedClass_b4750; }
