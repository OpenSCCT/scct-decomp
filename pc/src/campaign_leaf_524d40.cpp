// campaign_leaf_524d40.cpp -- free function at VA 0x10e24d40: passes two tables of four function
// addresses to the method at VA 0x10e38960 of its argument, the first with the values 5 and 7,
// the second with 7 and 5. The class, function and member names are invented; the addresses and
// the values are the binary's.

typedef void (*UnkType_10e24d40_Function)();

class UnkType_10e24d40_Table
{
public:
    UnkType_10e24d40_Function unk_00;
    UnkType_10e24d40_Function unk_04;
    UnkType_10e24d40_Function unk_08;
    UnkType_10e24d40_Function unk_0c;
};

class UnkType_10e24d40_Registry
{
public:
    void Unk_10e38960(UnkType_10e24d40_Table* Table, int From, int To);
};

void Unk_10e1a500();
void Unk_10e1a8f0();
void Unk_10e21520();
void Unk_10e238f0();
void Unk_10e24ad0();
void Unk_10e24b50();
void Unk_10e24c30();
void Unk_10e41760();

// Unk_10e24d40
void Unk_10e24d40(UnkType_10e24d40_Registry* Registry)
{
    UnkType_10e24d40_Table Table;
    Table.unk_00 = Unk_10e1a8f0;
    Table.unk_04 = Unk_10e24ad0;
    Table.unk_08 = Unk_10e24b50;
    Table.unk_0c = Unk_10e24c30;
    Registry->Unk_10e38960(&Table, 5, 7);
    Table.unk_00 = Unk_10e1a500;
    Table.unk_04 = Unk_10e238f0;
    Table.unk_08 = Unk_10e21520;
    Table.unk_0c = Unk_10e41760;
    Registry->Unk_10e38960(&Table, 7, 5);
}
