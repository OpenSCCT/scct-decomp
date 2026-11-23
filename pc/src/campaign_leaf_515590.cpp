// campaign_leaf_515590.cpp -- free function at VA 0x10e15590: passes two tables of four function
// addresses to the method at VA 0x10e38960 of its argument, the first with the values 4 and 20,
// the second with 20 and 4. The class, function and member names are invented; the addresses and
// the values are the binary's.

typedef void (*UnkType_10e15590_Function)();

class UnkType_10e15590_Table
{
public:
    UnkType_10e15590_Function unk_00;
    UnkType_10e15590_Function unk_04;
    UnkType_10e15590_Function unk_08;
    UnkType_10e15590_Function unk_0c;
};

class UnkType_10e15590_Registry
{
public:
    void Unk_10e38960(UnkType_10e15590_Table* Table, int From, int To);
};

void Unk_10e14170();
void Unk_10e141f0();
void Unk_10e14280();
void Unk_10e14350();
void Unk_10e143b0();
void Unk_10e14860();
void Unk_10e14a10();
void Unk_10e14d50();

// Unk_10e15590
void Unk_10e15590(UnkType_10e15590_Registry* Registry)
{
    UnkType_10e15590_Table Table;
    Table.unk_00 = Unk_10e14a10;
    Table.unk_04 = Unk_10e14170;
    Table.unk_08 = Unk_10e141f0;
    Table.unk_0c = Unk_10e14280;
    Registry->Unk_10e38960(&Table, 4, 20);
    Table.unk_00 = Unk_10e14d50;
    Table.unk_04 = Unk_10e14350;
    Table.unk_08 = Unk_10e143b0;
    Table.unk_0c = Unk_10e14860;
    Registry->Unk_10e38960(&Table, 20, 4);
}
