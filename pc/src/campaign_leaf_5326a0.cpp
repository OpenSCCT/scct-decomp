// campaign_leaf_5326a0.cpp -- cdecl function at VA 0x10e326a0: registers one set of four handler
// functions with the object it is given (method at VA 0x10e38960) for both orders of the pair of
// kinds (0x16, -1). guess: fills the pairwise dispatch tables. The handlers' signatures are not
// recovered; all names are invented.

typedef void (*UnkType_10e326a0_Handler)();

void Unk_10e32470();
void Unk_10e324a0();
void Unk_10e324c0();
void Unk_10e32540();

struct UnkType_10e326a0_Handlers
{
    UnkType_10e326a0_Handler unk_00;
    UnkType_10e326a0_Handler unk_04;
    UnkType_10e326a0_Handler unk_08;
    UnkType_10e326a0_Handler unk_0c;
};

class UnkType_10e326a0_Dispatcher
{
public:
    void Unk_10e38960(UnkType_10e326a0_Handlers* Handlers, int First, int Second);
};

// Unk_10e326a0
void Unk_10e326a0(UnkType_10e326a0_Dispatcher* Dispatcher)
{
    UnkType_10e326a0_Handlers Handlers;
    Handlers.unk_00 = Unk_10e32540;
    Handlers.unk_04 = Unk_10e32470;
    Handlers.unk_08 = Unk_10e324a0;
    Handlers.unk_0c = Unk_10e324c0;
    Dispatcher->Unk_10e38960(&Handlers, 0x16, -1);
    Dispatcher->Unk_10e38960(&Handlers, -1, 0x16);
}
