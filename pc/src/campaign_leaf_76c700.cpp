// campaign_leaf_76c700.cpp -- one function at file offset 0x76c700, preferred VA 0x1106c700. It
// releases the objects at 0x20, 0x34, 0x28, 0x2c, 0x24 and 0x30 that are set, passing the address
// of each member to the function at VA 0x1106eae0, 0x11062450, 0x11071590 (twice), 0x110710f0 and
// 0x1106cc10 respectively. The type and function names are invented; the offsets and the
// addresses are the binary's.

class UnkType_1106c700_A;
class UnkType_1106c700_B;
class UnkType_1106c700_C;
class UnkType_1106c700_D;
class UnkType_1106c700_E;

void Unk_1106eae0(UnkType_1106c700_A** Object);
void Unk_11062450(UnkType_1106c700_B** Object);
void Unk_11071590(UnkType_1106c700_C** Object);
void Unk_110710f0(UnkType_1106c700_D** Object);
void Unk_1106cc10(UnkType_1106c700_E** Object);

class UnkType_1106c700
{
public:
    void Unk_1106c700();

    unsigned char unk_0[0x20];
    UnkType_1106c700_A* unk_20;
    UnkType_1106c700_D* unk_24;
    UnkType_1106c700_C* unk_28;
    UnkType_1106c700_C* unk_2c;
    UnkType_1106c700_E* unk_30;
    UnkType_1106c700_B* unk_34;
};

// UnkType_1106c700::Unk_1106c700
void UnkType_1106c700::Unk_1106c700()
{
    if ( unk_20 != 0 )
    {
        Unk_1106eae0(&unk_20);
    }
    if ( unk_34 != 0 )
    {
        Unk_11062450(&unk_34);
    }
    if ( unk_28 != 0 )
    {
        Unk_11071590(&unk_28);
    }
    if ( unk_2c != 0 )
    {
        Unk_11071590(&unk_2c);
    }
    if ( unk_24 != 0 )
    {
        Unk_110710f0(&unk_24);
    }
    if ( unk_30 != 0 )
    {
        Unk_1106cc10(&unk_30);
    }
}
