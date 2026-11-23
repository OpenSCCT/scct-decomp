// campaign_leaf_5381b0.cpp -- cdecl function at VA 0x10e381b0: registers two sets of four handler
// functions with the object it is given (method at VA 0x10e38960), one for the pair of kinds
// (3, -1) and one for (-1, 3). guess: fills the pairwise dispatch tables. The
// handlers' signatures are not recovered; all names are invented.

typedef void (*UnkType_10e381b0_Handler)();

void Unk_10e35d90();
void Unk_10e37300();
void Unk_10e375c0();
void Unk_10e379c0();
void Unk_10e37e20();
void Unk_10e37ea0();
void Unk_10e37ee0();
void Unk_10e38160();

struct UnkType_10e381b0_Handlers
{
    UnkType_10e381b0_Handler unk_00;
    UnkType_10e381b0_Handler unk_04;
    UnkType_10e381b0_Handler unk_08;
    UnkType_10e381b0_Handler unk_0c;
};

class UnkType_10e381b0_Dispatcher
{
public:
    void Unk_10e38960(UnkType_10e381b0_Handlers* Handlers, int First, int Second);
};

// Unk_10e381b0
void Unk_10e381b0(UnkType_10e381b0_Dispatcher* Dispatcher)
{
    UnkType_10e381b0_Handlers Handlers;
    Handlers.unk_00 = Unk_10e38160;
    Handlers.unk_04 = Unk_10e37e20;
    Handlers.unk_08 = Unk_10e37ea0;
    Handlers.unk_0c = Unk_10e37ee0;
    Dispatcher->Unk_10e38960(&Handlers, 3, -1);
    Handlers.unk_00 = Unk_10e35d90;
    Handlers.unk_04 = Unk_10e379c0;
    Handlers.unk_08 = Unk_10e375c0;
    Handlers.unk_0c = Unk_10e37300;
    Dispatcher->Unk_10e38960(&Handlers, -1, 3);
}
