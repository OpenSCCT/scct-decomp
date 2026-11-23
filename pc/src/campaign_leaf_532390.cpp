// campaign_leaf_532390.cpp -- cdecl function at VA 0x10e32390: registers two sets of four handler
// functions with the object it is given (method at VA 0x10e38960), one for the pair of kinds
// (0xa, -1) and one for (-1, 0xa). guess: fills the pairwise dispatch tables. The
// handlers' signatures are not recovered; all names are invented.

typedef void (*UnkType_10e32390_Handler)();

void Unk_10e31b80();
void Unk_10e31bc0();
void Unk_10e31d10();
void Unk_10e32150();
void Unk_10e32350();
void Unk_10e338d0();
void Unk_10e33ab0();
void Unk_10e33c90();

struct UnkType_10e32390_Handlers
{
    UnkType_10e32390_Handler unk_00;
    UnkType_10e32390_Handler unk_04;
    UnkType_10e32390_Handler unk_08;
    UnkType_10e32390_Handler unk_0c;
};

class UnkType_10e32390_Dispatcher
{
public:
    void Unk_10e38960(UnkType_10e32390_Handlers* Handlers, int First, int Second);
};

// Unk_10e32390
void Unk_10e32390(UnkType_10e32390_Dispatcher* Dispatcher)
{
    UnkType_10e32390_Handlers Handlers;
    Handlers.unk_00 = Unk_10e32150;
    Handlers.unk_04 = Unk_10e33c90;
    Handlers.unk_08 = Unk_10e338d0;
    Handlers.unk_0c = Unk_10e33ab0;
    Dispatcher->Unk_10e38960(&Handlers, 0xa, -1);
    Handlers.unk_00 = Unk_10e32350;
    Handlers.unk_04 = Unk_10e31b80;
    Handlers.unk_08 = Unk_10e31bc0;
    Handlers.unk_0c = Unk_10e31d10;
    Dispatcher->Unk_10e38960(&Handlers, -1, 0xa);
}
