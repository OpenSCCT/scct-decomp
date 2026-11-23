// campaign_leaf_29bff0.cpp -- method at VA 0x10b9bff0 taking three values: asks the method at VA
// 0x10a58010 of the object at 0x518 for a result (starting at -1) with the values and the constants
// -1, 1, 0, 0, 0x1001; when the result is still negative, asks its method at VA 0x10a5c380 with
// 0, -1, 0, 1 instead; returns the result. The class, member and method names are invented; the
// offsets and the addresses are the binary's.

class UnkType_10b9bff0_518
{
public:
    void Unk_10a58010(int First, int Second, int* Result, int Third, int, int, int, int, int);
    void Unk_10a5c380(int First, int Second, int* Result, int Third, int, int, int, int);
};

class UnkType_10b9bff0
{
public:
    int Unk_10b9bff0(int First, int Second, int Third);

private:
    unsigned char unk_00[0x518];
    UnkType_10b9bff0_518* unk_518;
};

// UnkType_10b9bff0::Unk_10b9bff0
int UnkType_10b9bff0::Unk_10b9bff0(int First, int Second, int Third)
{
    int Result = -1;
    unk_518->Unk_10a58010(First, Second, &Result, Third, -1, 1, 0, 0, 0x1001);
    if ( Result < 0 )
    {
        unk_518->Unk_10a5c380(First, Second, &Result, Third, 0, -1, 0, 1);
    }
    return Result;
}
