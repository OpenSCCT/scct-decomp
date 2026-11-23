// campaign_leaf_482060.cpp -- function at VA 0x10d82060. It builds a 0x5c-byte local object
// (constructor at 0x10d95e80, destructor at 0x10d956a0) and fills it from its three arguments
// through 0x10d81f70; on failure it returns 0. Otherwise it calls the object's method at
// 0x10d94df0 with -1 and returns the word at 0x08 of the first argument. The class, function and
// parameter names are invented.

class UnkType_10d82060_Local
{
public:
    UnkType_10d82060_Local();
    ~UnkType_10d82060_Local();
    void Unk_10d94df0(int Value);

private:
    unsigned char unk_0[0x5c];
};

struct UnkType_10d82060_Source
{
    int unk_0;
    int unk_4;
    int unk_8;
};

bool Unk_10d81f70(UnkType_10d82060_Local* Local, UnkType_10d82060_Source* Source, int Second,
                  int Third);

// Unk_10d82060
int Unk_10d82060(UnkType_10d82060_Source* Source, int Second, int Third)
{
    UnkType_10d82060_Local Local;

    if ( !Unk_10d81f70(&Local, Source, Second, Third) )
    {
        return 0;
    }
    Local.Unk_10d94df0(-1);
    return Source->unk_8;
}
