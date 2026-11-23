// campaign_leaf_516870.cpp -- free function at VA 0x10e16870: passes two tables of four function
// addresses to the method at VA 0x10e38960 of its argument, the first with the values 1 and 20,
// the second with 20 and 1. The class, function and member names are invented; the addresses and
// the values are the binary's.

typedef void (*UnkType_10e16870_Function)();

class UnkType_10e16870_Table
{
public:
    UnkType_10e16870_Function unk_00;
    UnkType_10e16870_Function unk_04;
    UnkType_10e16870_Function unk_08;
    UnkType_10e16870_Function unk_0c;
};

class UnkType_10e16870_Registry
{
public:
    void Unk_10e38960(UnkType_10e16870_Table* Table, int From, int To);
};

void Unk_10e15860();
void Unk_10e158e0();
void Unk_10e15970();
void Unk_10e15c00();
void Unk_10e15c60();
void Unk_10e15f50();
void Unk_10e16280();
void Unk_10e16800();

// Unk_10e16870
void Unk_10e16870(UnkType_10e16870_Registry* Registry)
{
    UnkType_10e16870_Table Table;
    Table.unk_00 = Unk_10e15f50;
    Table.unk_04 = Unk_10e15860;
    Table.unk_08 = Unk_10e158e0;
    Table.unk_0c = Unk_10e15970;
    Registry->Unk_10e38960(&Table, 1, 20);
    Table.unk_00 = Unk_10e16800;
    Table.unk_04 = Unk_10e15c00;
    Table.unk_08 = Unk_10e15c60;
    Table.unk_0c = Unk_10e16280;
    Registry->Unk_10e38960(&Table, 20, 1);
}
