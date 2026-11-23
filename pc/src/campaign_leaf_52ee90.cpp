// campaign_leaf_52ee90.cpp -- free function at VA 0x10e2ee90: passes a table of four function
// addresses to the method at VA 0x10e38960 of its argument with the value 1 twice. The class,
// function and member names are invented; the addresses and the value are the binary's.

typedef void (*UnkType_10e2ee90_Function)();

class UnkType_10e2ee90_Table
{
public:
    UnkType_10e2ee90_Function unk_00;
    UnkType_10e2ee90_Function unk_04;
    UnkType_10e2ee90_Function unk_08;
    UnkType_10e2ee90_Function unk_0c;
};

class UnkType_10e2ee90_Registry
{
public:
    void Unk_10e38960(UnkType_10e2ee90_Table* Table, int From, int To);
};

void Unk_10e2ddf0();
void Unk_10e2df40();
void Unk_10e2e7a0();
void Unk_10e41760();

// Unk_10e2ee90
void Unk_10e2ee90(UnkType_10e2ee90_Registry* Registry)
{
    UnkType_10e2ee90_Table Table;
    Table.unk_00 = Unk_10e2ddf0;
    Table.unk_04 = Unk_10e2df40;
    Table.unk_08 = Unk_10e2e7a0;
    Table.unk_0c = Unk_10e41760;
    Registry->Unk_10e38960(&Table, 1, 1);
}
