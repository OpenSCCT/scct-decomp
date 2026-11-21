// Linear search of an INT array held at +0x2c (Data) / +0x30 (Num) of an
// unidentified owner object; returns the index of Value or INDEX_NONE (-1).
// Class name is neutral: no vtable or string evidence for the owner.
typedef int INT;

struct UnnamedClass_118000
{
    char Pad[0x2c];
    INT *Data;
    INT  Num;

    INT FindItem(INT Value);
};

__declspec(noinline) INT UnnamedClass_118000::FindItem(INT Value)
{
    for (INT i = 0; i < Num; i++)
        if (Data[i] == Value)
            return i;
    return -1;
}

// Scaffolding for the link, not part of the unit.
INT Driver_118000(UnnamedClass_118000 *Obj, INT Value)
{
    return Obj->FindItem(Value);
}
