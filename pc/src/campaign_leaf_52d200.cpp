// campaign_leaf_52d200.cpp -- free function at VA 0x10e2d200: passes a table of four function
// addresses to the method at VA 0x10e38960 of its argument with the value 4 twice. The class,
// function and member names are invented; the addresses and the value are the binary's.

typedef void (*UnkType_10e2d200_Function)();

class UnkType_10e2d200_Table
{
public:
    UnkType_10e2d200_Function unk_00;
    UnkType_10e2d200_Function unk_04;
    UnkType_10e2d200_Function unk_08;
    UnkType_10e2d200_Function unk_0c;
};

class UnkType_10e2d200_Registry
{
public:
    void Unk_10e38960(UnkType_10e2d200_Table* Table, int From, int To);
};

void Unk_10e2caf0();
void Unk_10e2ce60();
void Unk_10e2d100();
void Unk_10e41760();

// Unk_10e2d200
void Unk_10e2d200(UnkType_10e2d200_Registry* Registry)
{
    UnkType_10e2d200_Table Table;
    Table.unk_00 = Unk_10e2caf0;
    Table.unk_04 = Unk_10e2d100;
    Table.unk_08 = Unk_10e2ce60;
    Table.unk_0c = Unk_10e41760;
    Registry->Unk_10e38960(&Table, 4, 4);
}
