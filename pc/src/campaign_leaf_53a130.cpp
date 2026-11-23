// campaign_leaf_53a130.cpp -- cdecl function at VA 0x10e3a130: registers two sets of four handler
// functions with the object it is given (method at VA 0x10e38960), one for the pair of kinds
// (-1, 9) and one for (9, -1). guess: fills the pairwise dispatch tables. The
// handlers' signatures are not recovered; all names are invented.

typedef void (*UnkType_10e3a130_Handler)();

void Unk_10e39190();
void Unk_10e39470();
void Unk_10e39750();
void Unk_10e39930();
void Unk_10e39970();
void Unk_10e399e0();
void Unk_10e39ef0();
void Unk_10e3a0f0();

struct UnkType_10e3a130_Handlers
{
    UnkType_10e3a130_Handler unk_00;
    UnkType_10e3a130_Handler unk_04;
    UnkType_10e3a130_Handler unk_08;
    UnkType_10e3a130_Handler unk_0c;
};

class UnkType_10e3a130_Dispatcher
{
public:
    void Unk_10e38960(UnkType_10e3a130_Handlers* Handlers, int First, int Second);
};

// Unk_10e3a130
void Unk_10e3a130(UnkType_10e3a130_Dispatcher* Dispatcher)
{
    UnkType_10e3a130_Handlers Handlers;
    Handlers.unk_00 = Unk_10e3a0f0;
    Handlers.unk_04 = Unk_10e39930;
    Handlers.unk_08 = Unk_10e39970;
    Handlers.unk_0c = Unk_10e399e0;
    Dispatcher->Unk_10e38960(&Handlers, -1, 9);
    Handlers.unk_00 = Unk_10e39ef0;
    Handlers.unk_04 = Unk_10e39750;
    Handlers.unk_08 = Unk_10e39190;
    Handlers.unk_0c = Unk_10e39470;
    Dispatcher->Unk_10e38960(&Handlers, 9, -1);
}
