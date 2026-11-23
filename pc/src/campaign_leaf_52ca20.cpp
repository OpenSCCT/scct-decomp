// campaign_leaf_52ca20.cpp -- free function at VA 0x10e2ca20: passes two tables of four function
// addresses to the method at VA 0x10e38960 of its argument, the first with the values 7 and 4,
// the second with 4 and 7. The class, function and member names are invented; the addresses and
// the values are the binary's.

typedef void (*UnkType_10e2ca20_Function)();

class UnkType_10e2ca20_Table
{
public:
    UnkType_10e2ca20_Function unk_00;
    UnkType_10e2ca20_Function unk_04;
    UnkType_10e2ca20_Function unk_08;
    UnkType_10e2ca20_Function unk_0c;
};

class UnkType_10e2ca20_Registry
{
public:
    void Unk_10e38960(UnkType_10e2ca20_Table* Table, int From, int To);
};

void Unk_10e2b3b0();
void Unk_10e2b450();
void Unk_10e2c230();
void Unk_10e2c5a0();
void Unk_10e2c7b0();
void Unk_10e2c830();
void Unk_10e2c910();
void Unk_10e41760();

// Unk_10e2ca20
void Unk_10e2ca20(UnkType_10e2ca20_Registry* Registry)
{
    UnkType_10e2ca20_Table Table;
    Table.unk_00 = Unk_10e2b450;
    Table.unk_04 = Unk_10e2c7b0;
    Table.unk_08 = Unk_10e2c830;
    Table.unk_0c = Unk_10e2c910;
    Registry->Unk_10e38960(&Table, 7, 4);
    Table.unk_00 = Unk_10e2b3b0;
    Table.unk_04 = Unk_10e2c5a0;
    Table.unk_08 = Unk_10e2c230;
    Table.unk_0c = Unk_10e41760;
    Registry->Unk_10e38960(&Table, 4, 7);
}
