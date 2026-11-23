// campaign_leaf_51a3b0.cpp -- free function at VA 0x10e1a3b0: passes two tables of four function
// addresses to the method at VA 0x10e38960 of its argument, the first with the values 5 and 9,
// the second with 9 and 5. The class, function and member names are invented; the addresses and
// the values are the binary's.

typedef void (*UnkType_10e1a3b0_Function)();

class UnkType_10e1a3b0_Table
{
public:
    UnkType_10e1a3b0_Function unk_00;
    UnkType_10e1a3b0_Function unk_04;
    UnkType_10e1a3b0_Function unk_08;
    UnkType_10e1a3b0_Function unk_0c;
};

class UnkType_10e1a3b0_Registry
{
public:
    void Unk_10e38960(UnkType_10e1a3b0_Table* Table, int From, int To);
};

void Unk_10e18870();
void Unk_10e18960();
void Unk_10e19420();
void Unk_10e19d10();
void Unk_10e1a140();
void Unk_10e1a1c0();
void Unk_10e1a2a0();
void Unk_10e41760();

// Unk_10e1a3b0
void Unk_10e1a3b0(UnkType_10e1a3b0_Registry* Registry)
{
    UnkType_10e1a3b0_Table Table;
    Table.unk_00 = Unk_10e18960;
    Table.unk_04 = Unk_10e1a140;
    Table.unk_08 = Unk_10e1a1c0;
    Table.unk_0c = Unk_10e1a2a0;
    Registry->Unk_10e38960(&Table, 5, 9);
    Table.unk_00 = Unk_10e18870;
    Table.unk_04 = Unk_10e19d10;
    Table.unk_08 = Unk_10e19420;
    Table.unk_0c = Unk_10e41760;
    Registry->Unk_10e38960(&Table, 9, 5);
}
