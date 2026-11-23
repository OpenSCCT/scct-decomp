// campaign_leaf_52b2e0.cpp -- free function at VA 0x10e2b2e0: passes two tables of four function
// addresses to the method at VA 0x10e38960 of its argument, the first with the values 5 and 4,
// the second with 4 and 5. The class, function and member names are invented; the addresses and
// the values are the binary's.

typedef void (*UnkType_10e2b2e0_Function)();

class UnkType_10e2b2e0_Table
{
public:
    UnkType_10e2b2e0_Function unk_00;
    UnkType_10e2b2e0_Function unk_04;
    UnkType_10e2b2e0_Function unk_08;
    UnkType_10e2b2e0_Function unk_0c;
};

class UnkType_10e2b2e0_Registry
{
public:
    void Unk_10e38960(UnkType_10e2b2e0_Table* Table, int From, int To);
};

void Unk_10e2a0f0();
void Unk_10e2a1c0();
void Unk_10e2ab60();
void Unk_10e2af10();
void Unk_10e2b070();
void Unk_10e2b0f0();
void Unk_10e2b1d0();
void Unk_10e41760();

// Unk_10e2b2e0
void Unk_10e2b2e0(UnkType_10e2b2e0_Registry* Registry)
{
    UnkType_10e2b2e0_Table Table;
    Table.unk_00 = Unk_10e2a1c0;
    Table.unk_04 = Unk_10e2b070;
    Table.unk_08 = Unk_10e2b0f0;
    Table.unk_0c = Unk_10e2b1d0;
    Registry->Unk_10e38960(&Table, 5, 4);
    Table.unk_00 = Unk_10e2a0f0;
    Table.unk_04 = Unk_10e2af10;
    Table.unk_08 = Unk_10e2ab60;
    Table.unk_0c = Unk_10e41760;
    Registry->Unk_10e38960(&Table, 4, 5);
}
