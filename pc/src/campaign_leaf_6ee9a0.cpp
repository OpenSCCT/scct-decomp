// campaign_leaf_6ee9a0.cpp -- constructor at VA 0x10fee9a0 of a class whose vtable is at VA 0x1116fc90:
// passes its three arguments to the base constructor at VA 0x10e038c0 and adds nothing. The class
// names are invented; the addresses are the binary's.

class UnkType_10fee9a0_Base
{
public:
    UnkType_10fee9a0_Base(int First, int Second, int Third);
    virtual ~UnkType_10fee9a0_Base();
};

class UnkType_10fee9a0 : public UnkType_10fee9a0_Base
{
public:
    UnkType_10fee9a0(int First, int Second, int Third);
};

// UnkType_10fee9a0::UnkType_10fee9a0
UnkType_10fee9a0::UnkType_10fee9a0(int First, int Second, int Third)
    : UnkType_10fee9a0_Base(First, Second, Third)
{
}
