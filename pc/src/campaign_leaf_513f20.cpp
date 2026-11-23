// campaign_leaf_513f20.cpp -- free function at VA 0x10e13f20: passes two tables of four function
// addresses to the method at VA 0x10e38960 of its argument, the first with the values 7 and 20,
// the second with 20 and 7. The class, function and member names are invented; the addresses and
// the values are the binary's.

typedef void (*UnkType_10e13f20_Function)();

class UnkType_10e13f20_Table
{
public:
    UnkType_10e13f20_Function unk_00;
    UnkType_10e13f20_Function unk_04;
    UnkType_10e13f20_Function unk_08;
    UnkType_10e13f20_Function unk_0c;
};

class UnkType_10e13f20_Registry
{
public:
    void Unk_10e38960(UnkType_10e13f20_Table* Table, int From, int To);
};

void Unk_10e12b30();
void Unk_10e12bb0();
void Unk_10e12c40();
void Unk_10e12cd0();
void Unk_10e12d30();
void Unk_10e13410();
void Unk_10e135c0();
void Unk_10e13ef0();

// Unk_10e13f20
void Unk_10e13f20(UnkType_10e13f20_Registry* Registry)
{
    UnkType_10e13f20_Table Table;
    Table.unk_00 = Unk_10e135c0;
    Table.unk_04 = Unk_10e12b30;
    Table.unk_08 = Unk_10e12bb0;
    Table.unk_0c = Unk_10e12c40;
    Registry->Unk_10e38960(&Table, 7, 20);
    Table.unk_00 = Unk_10e13ef0;
    Table.unk_04 = Unk_10e12cd0;
    Table.unk_08 = Unk_10e12d30;
    Table.unk_0c = Unk_10e13410;
    Registry->Unk_10e38960(&Table, 20, 7);
}
