// campaign_leaf_54f4d0.cpp -- thiscall method at VA 0x10e4f4d0: clears the two values its first
// arguments point to, sets the members at 0x00 and 0x04 to 1e-5 and the largest float, asks the
// object it is given (method at VA 0x10e4f240) for a result, which it stores at 0x44 of that
// object, and when the result is 1 returns the method at VA 0x10e4f340; otherwise returns 2. All
// names are invented.

class UnkType_10e4f4d0;

class UnkType_10e4f4d0_Query
{
public:
    char Unk_10e4f240(int Value, UnkType_10e4f4d0* Owner, float* Limit);

    int unk_00[17];
    char unk_44;
};

class UnkType_10e4f4d0
{
public:
    int Unk_10e4f340(float* First, float* Second, UnkType_10e4f4d0_Query* Query, int Value);
    int Unk_10e4f4d0(float* First, float* Second, UnkType_10e4f4d0_Query* Query, int Value);

private:
    float unk_00;
    float unk_04;
};

// UnkType_10e4f4d0::Unk_10e4f4d0
int UnkType_10e4f4d0::Unk_10e4f4d0(float* First, float* Second, UnkType_10e4f4d0_Query* Query,
                                   int Value)
{
    *Second = 0.0f;
    *First = 0.0f;
    unk_04 = 3.402823466e+38f;
    unk_00 = 1e-5f;
    char Result = Query->Unk_10e4f240(Value, this, &unk_04);
    Query->unk_44 = Result;
    if ( Result == 1 )
    {
        return Unk_10e4f340(First, Second, Query, Value);
    }
    return 2;
}
