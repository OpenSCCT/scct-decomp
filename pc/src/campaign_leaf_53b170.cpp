// campaign_leaf_53b170.cpp -- cdecl function at VA 0x10e3b170: registers two sets of four handler
// functions with the object it is given (method at VA 0x10e38960), one for the pair of kinds
// (-1, 0x11) and one for (0x11, -1). guess: fills the pairwise dispatch tables. The
// handlers' signatures are not recovered; all names are invented.

typedef void (*UnkType_10e3b170_Handler)();

void Unk_10e3a330();
void Unk_10e3a670();
void Unk_10e3a930();
void Unk_10e3ab10();
void Unk_10e3ac50();
void Unk_10e3ac90();
void Unk_10e3af20();
void Unk_10e3af60();

struct UnkType_10e3b170_Handlers
{
    UnkType_10e3b170_Handler unk_00;
    UnkType_10e3b170_Handler unk_04;
    UnkType_10e3b170_Handler unk_08;
    UnkType_10e3b170_Handler unk_0c;
};

class UnkType_10e3b170_Dispatcher
{
public:
    void Unk_10e38960(UnkType_10e3b170_Handlers* Handlers, int First, int Second);
};

// Unk_10e3b170
void Unk_10e3b170(UnkType_10e3b170_Dispatcher* Dispatcher)
{
    UnkType_10e3b170_Handlers Handlers;
    Handlers.unk_00 = Unk_10e3af20;
    Handlers.unk_04 = Unk_10e3ac50;
    Handlers.unk_08 = Unk_10e3ac90;
    Handlers.unk_0c = Unk_10e3af60;
    Dispatcher->Unk_10e38960(&Handlers, -1, 0x11);
    Handlers.unk_00 = Unk_10e3a330;
    Handlers.unk_04 = Unk_10e3ab10;
    Handlers.unk_08 = Unk_10e3a930;
    Handlers.unk_0c = Unk_10e3a670;
    Dispatcher->Unk_10e38960(&Handlers, 0x11, -1);
}
