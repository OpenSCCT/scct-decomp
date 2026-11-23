// campaign_leaf_526650.cpp -- free function at VA 0x10e26650: passes a table of four function
// addresses to the method at VA 0x10e38960 of its argument with the value 7 twice. The class,
// function and member names are invented; the addresses and the value are the binary's.

typedef void (*UnkType_10e26650_Function)();

class UnkType_10e26650_Table
{
public:
    UnkType_10e26650_Function unk_00;
    UnkType_10e26650_Function unk_04;
    UnkType_10e26650_Function unk_08;
    UnkType_10e26650_Function unk_0c;
};

class UnkType_10e26650_Registry
{
public:
    void Unk_10e38960(UnkType_10e26650_Table* Table, int From, int To);
};

void Unk_10e24ea0();
void Unk_10e25df0();
void Unk_10e26330();
void Unk_10e41760();

// Unk_10e26650
void Unk_10e26650(UnkType_10e26650_Registry* Registry)
{
    UnkType_10e26650_Table Table;
    Table.unk_00 = Unk_10e24ea0;
    Table.unk_04 = Unk_10e26330;
    Table.unk_08 = Unk_10e25df0;
    Table.unk_0c = Unk_10e41760;
    Registry->Unk_10e38960(&Table, 7, 7);
}
