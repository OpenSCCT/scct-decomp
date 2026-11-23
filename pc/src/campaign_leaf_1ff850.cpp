// campaign_leaf_1ff850.cpp -- destructor at VA 0x10aff850 of a table of 40 slots, each a flag byte
// and a 0x18-byte object whose destructor is at VA 0x10aff630. For every slot (indexed modulo 40)
// whose flag is set it sets the flag, destroys the object and clears the flag; then the slot array
// is destroyed, which runs the object destructor on all 40 slots in reverse. The class and member
// names are invented.

class UnkType_10aff630
{
public:
    ~UnkType_10aff630();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
};

struct UnkType_10aff630_Slot
{
    bool bUsed;
    UnkType_10aff630 Value;
};

class UnkType_10aff850
{
public:
    ~UnkType_10aff850();

private:
    UnkType_10aff630_Slot unk_000[40];
};

// UnkType_10aff850::~UnkType_10aff850
UnkType_10aff850::~UnkType_10aff850()
{
    for ( int i = 0; i < 40; i++ )
    {
        if ( unk_000[(unsigned int)i % 40].bUsed )
        {
            unk_000[(unsigned int)i % 40].bUsed = true;
            unk_000[(unsigned int)i % 40].Value.~UnkType_10aff630();
            unk_000[(unsigned int)i % 40].bUsed = false;
        }
    }
}
