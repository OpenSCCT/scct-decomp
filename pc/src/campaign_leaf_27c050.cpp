// campaign_leaf_27c050.cpp -- method at VA 0x10b7c050: when flag 8 at 0x748 is set, moves the float
// at 0x96c toward the float at 0x970 by the float at 0x974 times the float at 0x75c of the object
// at 0x78, stopping on it; once it is there and flag 0x10 is set, clears flag 8 and calls the
// method at VA 0x109d5310 of the object at 0x64 with 15 and 0. The class, member, method and local
// names are invented; the offsets, the constants and the address are the binary's.

class UnkType_10b7c050_Timer
{
public:
    char unk_0[0x75c];
    float unk_75c;
};

class UnkType_10b7c050_Notify
{
public:
    void Unk_109d5310(int Event, int Value);
};

class UnkType_10b7c050
{
public:
    void Unk_10b7c050();

private:
    char unk_0[0x64];
    UnkType_10b7c050_Notify* unk_64;
    char unk_68[0x78 - 0x68];
    UnkType_10b7c050_Timer* unk_78;
    char unk_7c[0x748 - 0x7c];
    unsigned int unk_748_0 : 3;
    unsigned int unk_748_3 : 1;
    unsigned int unk_748_4 : 1;
    char unk_74c[0x96c - 0x74c];
    float unk_96c;
    float unk_970;
    float unk_974;
};

// UnkType_10b7c050::Unk_10b7c050
void UnkType_10b7c050::Unk_10b7c050()
{
    if ( unk_748_3 )
    {
        float Current = unk_96c;
        bool bReached = Current == unk_970;

        if ( Current < unk_970 )
        {
            Current += unk_78->unk_75c * unk_974;
            if ( Current > unk_970 )
            {
                Current = unk_970;
                bReached = true;
            }
        }
        else if ( Current > unk_970 )
        {
            Current -= unk_78->unk_75c * unk_974;
            if ( Current < unk_970 )
            {
                Current = unk_970;
                bReached = true;
            }
        }
        unk_96c = Current;
        if ( bReached && unk_748_4 )
        {
            unk_748_3 = 0;
            unk_64->Unk_109d5310(15, 0);
        }
    }
}
