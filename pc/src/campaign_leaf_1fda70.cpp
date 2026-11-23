// campaign_leaf_1fda70.cpp -- destructor at VA 0x10afda70 of a table of 40 slots, each a flag byte
// and a 0x18-byte object whose destructor is at VA 0x10afd850. For every slot (indexed modulo 40)
// whose flag is set it sets the flag, destroys the object and clears the flag; then the slot array
// is destroyed, which runs the object destructor on all 40 slots in reverse. The class and member
// names are invented.

class UnkType_10afd850
{
public:
    ~UnkType_10afd850();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
};

struct UnkType_10afd850_Slot
{
    bool bUsed;
    UnkType_10afd850 Value;
};

class UnkType_10afda70
{
public:
    ~UnkType_10afda70();

private:
    UnkType_10afd850_Slot unk_000[40];
};

// UnkType_10afda70::~UnkType_10afda70
UnkType_10afda70::~UnkType_10afda70()
{
    for ( int i = 0; i < 40; i++ )
    {
        if ( unk_000[(unsigned int)i % 40].bUsed )
        {
            unk_000[(unsigned int)i % 40].bUsed = true;
            unk_000[(unsigned int)i % 40].Value.~UnkType_10afd850();
            unk_000[(unsigned int)i % 40].bUsed = false;
        }
    }
}
