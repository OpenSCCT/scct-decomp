// campaign_leaf_518770.cpp -- free function at VA 0x10e18770: passes two tables of four function
// addresses to the method at VA 0x10e38960 of its argument, the first with the values 1 and 12,
// the second with 12 and 1. The class, function and member names are invented; the addresses and
// the values are the binary's.

typedef void (*UnkType_10e18770_Function)();

class UnkType_10e18770_Table
{
public:
    UnkType_10e18770_Function unk_00;
    UnkType_10e18770_Function unk_04;
    UnkType_10e18770_Function unk_08;
    UnkType_10e18770_Function unk_0c;
};

class UnkType_10e18770_Registry
{
public:
    void Unk_10e38960(UnkType_10e18770_Table* Table, int From, int To);
};

void Unk_10e173e0();
void Unk_10e175a0();
void Unk_10e17a00();
void Unk_10e17de0();
void Unk_10e17e50();
void Unk_10e183b0();
void Unk_10e18730();
void Unk_10e41760();

// Unk_10e18770
void Unk_10e18770(UnkType_10e18770_Registry* Registry)
{
    UnkType_10e18770_Table Table;
    Table.unk_00 = Unk_10e18730;
    Table.unk_04 = Unk_10e175a0;
    Table.unk_08 = Unk_10e17de0;
    Table.unk_0c = Unk_10e17e50;
    Registry->Unk_10e38960(&Table, 1, 12);
    Table.unk_00 = Unk_10e183b0;
    Table.unk_04 = Unk_10e173e0;
    Table.unk_08 = Unk_10e17a00;
    Table.unk_0c = Unk_10e41760;
    Registry->Unk_10e38960(&Table, 12, 1);
}
