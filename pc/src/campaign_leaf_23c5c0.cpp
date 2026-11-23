// campaign_leaf_23c5c0.cpp -- a member function at VA 0x10b3c5c0 taking a flag: when it is set it
// passes this and the functions at VA 0x10b3c3b0, 0x10b3bbc0, 0x10b3bf90, 0x10b3c0a0 and 0x10b3c1b0
// to the free functions at VA 0x10aa4740, 0x10aa4760, 0x10aa47c0, 0x10aa47e0 and 0x10aa4800 in
// turn; otherwise it passes 0 and 0 to each of them. guess: installs or removes callbacks. The
// class, function, method and parameter names are invented; the addresses are the binary's.

void Unk_10b3c3b0();
void Unk_10b3bbc0();
void Unk_10b3bf90();
void Unk_10b3c0a0();
void Unk_10b3c1b0();

void Unk_10aa4740(void* Owner, void (*Callback)());
void Unk_10aa4760(void* Owner, void (*Callback)());
void Unk_10aa47c0(void* Owner, void (*Callback)());
void Unk_10aa47e0(void* Owner, void (*Callback)());
void Unk_10aa4800(void* Owner, void (*Callback)());

class UnkType_10b3c5c0
{
public:
    void Unk_10b3c5c0(bool Enable);
};

// UnkType_10b3c5c0::Unk_10b3c5c0
void UnkType_10b3c5c0::Unk_10b3c5c0(bool Enable)
{
    if ( Enable )
    {
        Unk_10aa4740(this, Unk_10b3c3b0);
        Unk_10aa4760(this, Unk_10b3bbc0);
        Unk_10aa47c0(this, Unk_10b3bf90);
        Unk_10aa47e0(this, Unk_10b3c0a0);
        Unk_10aa4800(this, Unk_10b3c1b0);
    }
    else
    {
        Unk_10aa4740(0, 0);
        Unk_10aa4760(0, 0);
        Unk_10aa47c0(0, 0);
        Unk_10aa47e0(0, 0);
        Unk_10aa4800(0, 0);
    }
}
