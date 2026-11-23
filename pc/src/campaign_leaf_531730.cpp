// campaign_leaf_531730.cpp -- cdecl function at VA 0x10e31730: registers two sets of four handler
// functions with the object it is given (method at VA 0x10e38960), one for the pair of kinds
// (0xd, 0x10) and one for (0x10, 0xd). guess: fills the pairwise dispatch tables. The
// handlers' signatures are not recovered; all names are invented.

typedef void (*UnkType_10e31730_Handler)();

void Unk_10e2f790();
void Unk_10e2fc50();
void Unk_10e30490();
void Unk_10e30920();
void Unk_10e30960();
void Unk_10e31210();
void Unk_10e31290();
void Unk_10e316f0();

struct UnkType_10e31730_Handlers
{
    UnkType_10e31730_Handler unk_00;
    UnkType_10e31730_Handler unk_04;
    UnkType_10e31730_Handler unk_08;
    UnkType_10e31730_Handler unk_0c;
};

class UnkType_10e31730_Dispatcher
{
public:
    void Unk_10e38960(UnkType_10e31730_Handlers* Handlers, int First, int Second);
};

// Unk_10e31730
void Unk_10e31730(UnkType_10e31730_Dispatcher* Dispatcher)
{
    UnkType_10e31730_Handlers Handlers;
    Handlers.unk_00 = Unk_10e316f0;
    Handlers.unk_04 = Unk_10e30920;
    Handlers.unk_08 = Unk_10e30960;
    Handlers.unk_0c = Unk_10e31290;
    Dispatcher->Unk_10e38960(&Handlers, 0xd, 0x10);
    Handlers.unk_00 = Unk_10e31210;
    Handlers.unk_04 = Unk_10e2f790;
    Handlers.unk_08 = Unk_10e2fc50;
    Handlers.unk_0c = Unk_10e30490;
    Dispatcher->Unk_10e38960(&Handlers, 0x10, 0xd);
}
