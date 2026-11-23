// campaign_leaf_29c560.cpp -- method at VA 0x10b9c560: when bit 1 of the word at 0x538 of the object
// at 0x6ec of the object at 0x41c is set, clears the counter at 0x990 and returns 2; otherwise
// passes the counter as a float and 10 to the method at VA 0x10cee590, increments the counter and
// returns 0 when the result is below 7, and decrements it and returns 2 otherwise. The class,
// member and method names are invented; the offsets and the address are the binary's.

class UnkType_10b9c560_6ec
{
public:
    unsigned char unk_00[0x538];
    int unk_538;
};

class UnkType_10b9c560_41c
{
public:
    unsigned char unk_00[0x6ec];
    UnkType_10b9c560_6ec* unk_6ec;
};

class UnkType_10b9c560
{
public:
    int Unk_10b9c560();
    float Unk_10cee590(float Value, float Limit);

private:
    unsigned char unk_00[0x41c];
    UnkType_10b9c560_41c* unk_41c;
    unsigned char unk_420[0x990 - 0x420];
    int unk_990;
};

// UnkType_10b9c560::Unk_10b9c560
int UnkType_10b9c560::Unk_10b9c560()
{
    if ( unk_41c->unk_6ec->unk_538 & 2 )
    {
        unk_990 = 0;
        return 2;
    }
    if ( Unk_10cee590((float)unk_990, 10.0f) < 7.0f )
    {
        unk_990++;
        return 0;
    }
    unk_990--;
    return 2;
}
