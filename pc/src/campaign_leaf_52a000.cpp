// campaign_leaf_52a000.cpp -- free function at VA 0x10e2a000: passes two tables of four function
// addresses to the method at VA 0x10e38960 of its argument, the first with the values 6 and 4,
// the second with 4 and 6. The class, function and member names are invented; the addresses and
// the values are the binary's.

typedef void (*UnkType_10e2a000_Function)();

class UnkType_10e2a000_Table
{
public:
    UnkType_10e2a000_Function unk_00;
    UnkType_10e2a000_Function unk_04;
    UnkType_10e2a000_Function unk_08;
    UnkType_10e2a000_Function unk_0c;
};

class UnkType_10e2a000_Registry
{
public:
    void Unk_10e38960(UnkType_10e2a000_Table* Table, int From, int To);
};

void Unk_10e28a40();
void Unk_10e28ad0();
void Unk_10e29740();
void Unk_10e29b60();
void Unk_10e29dc0();
void Unk_10e29e40();
void Unk_10e29ef0();
void Unk_10e41760();

// Unk_10e2a000
void Unk_10e2a000(UnkType_10e2a000_Registry* Registry)
{
    UnkType_10e2a000_Table Table;
    Table.unk_00 = Unk_10e28ad0;
    Table.unk_04 = Unk_10e29dc0;
    Table.unk_08 = Unk_10e29e40;
    Table.unk_0c = Unk_10e29ef0;
    Registry->Unk_10e38960(&Table, 6, 4);
    Table.unk_00 = Unk_10e28a40;
    Table.unk_04 = Unk_10e29b60;
    Table.unk_08 = Unk_10e29740;
    Table.unk_0c = Unk_10e41760;
    Registry->Unk_10e38960(&Table, 4, 6);
}
