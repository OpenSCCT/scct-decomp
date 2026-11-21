// RVA 0xeeff0. Neutral names: the owning class is not identified yet.
typedef int INT;
typedef float FLOAT;
typedef double DOUBLE;

#pragma pack(push, 4)

class UnnamedItem_eeff0
{
public:
    virtual void Vf0();
    virtual void Vf1();
    virtual void Vf2();
    virtual void Vf3(INT Flag);
    char Pad04[0x6c - 4];
    INT State;
};

struct UnnamedLink_eeff0
{
    char Pad00[0x44];
    INT Rate;
};

class UnnamedClass_eeff0
{
public:
    char Pad00[0x2c];
    UnnamedItem_eeff0 **Items;   // TArray data
    INT ItemCount;               // TArray num
    INT ItemMax;
    UnnamedLink_eeff0 *Link;
    char Pad3c[0x44 - 0x3c];
    DOUBLE Time;
    char Pad4c[0x80 - 0x4c];
    INT Value80;
    INT Value84;
    INT Pad88;
    INT Budget;
    INT Rate;

    void Tick(FLOAT DeltaTime);
};

#pragma pack(pop)

void UnnamedClass_eeff0::Tick(FLOAT DeltaTime)
{
    Time += DeltaTime;
    Value84 = 0;
    Value80 = 0;
    FLOAT Amount = (Link ? (FLOAT)Link->Rate : (FLOAT)Rate) * DeltaTime;
    Budget -= (INT)Amount;
    FLOAT Max = Amount + Amount;
    if (Budget < -Max)
        Budget = (INT)-Max;
    if (!Link)
    {
        for (INT i = ItemCount - 1; i >= 0; i--)
        {
            UnnamedItem_eeff0 *Item = Items[i];
            if (Item->State == 1 || Item->State == 4)
                Item->Vf3(1);
        }
    }
}
