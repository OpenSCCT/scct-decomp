// campaign_leaf_4f9b40.cpp -- constructor at VA 0x10df9b40: constructs its base (VA 0x10d9d560) and
// three rings of forty slots at 0x08, 0xb8 and 0x208, whose constructors clear their leading flag,
// the flag of every slot and their trailing flag. The class and member names are invented; the
// offsets and the address are the binary's.

template<class T> class UnkType_10df9b40_Slots
{
public:
    UnkType_10df9b40_Slots()
    {
        Flag = false;
    }

    struct Slot
    {
        Slot()
            : Used(false)
        {
        }

        bool Used;
        T Value;
    };

    Slot Slots[40];
    T Last;
    bool Flag;
};

template<class T> class UnkType_10df9b40_Ring
{
public:
    UnkType_10df9b40_Ring()
        : unk_00(false)
    {
    }

    bool unk_00;
    UnkType_10df9b40_Slots<T> Slots;
};

class UnkType_10df9b40_Base
{
public:
    UnkType_10df9b40_Base();

    int unk_00;
    int unk_04;
};

class UnkType_10df9b40 : public UnkType_10df9b40_Base
{
public:
    UnkType_10df9b40();

    UnkType_10df9b40_Ring<short> unk_08;
    int unk_b0;
    int unk_b4;
    UnkType_10df9b40_Ring<int> unk_b8;
    int unk_204;
    UnkType_10df9b40_Ring<short> unk_208;
};

// UnkType_10df9b40::UnkType_10df9b40
UnkType_10df9b40::UnkType_10df9b40()
{
}
