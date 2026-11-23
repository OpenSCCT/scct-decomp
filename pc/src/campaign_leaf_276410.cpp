// campaign_leaf_276410.cpp -- method at VA 0x10b76410 taking an index: reaches an object through the
// object at 0x1c (its byte at 0x0c passed to the method at VA 0x10a0e220 of its object at 0x04,
// then the method at VA 0x10a45b50 of the result's object at 0x64); when that object and its words
// at 0x4a0 and 0x400 are set, returns what the method at VA 0x1099d870 of the object at 0x400
// gives for the index when the index is below the count from its method at VA 0x1099d840, and 0
// otherwise. The class, member and method names are invented; the offsets and the addresses are
// the binary's.

class UnkType_10b76410_400
{
public:
    int Unk_1099d840();
    int Unk_1099d870(int Index);
};

class UnkType_10b76410_Found
{
public:
    unsigned char unk_00[0x400];
    UnkType_10b76410_400* unk_400;
    unsigned char unk_404[0x4a0 - 0x404];
    int unk_4a0;
};

class UnkType_10b76410_64
{
public:
    UnkType_10b76410_Found* Unk_10a45b50();
};

class UnkType_10b76410_Entry
{
public:
    unsigned char unk_00[0x64];
    UnkType_10b76410_64* unk_64;
};

class UnkType_10b76410_04
{
public:
    UnkType_10b76410_Entry* Unk_10a0e220(unsigned char Key);
};

class UnkType_10b76410_1c
{
public:
    int unk_00;
    UnkType_10b76410_04* unk_04;
    int unk_08;
    unsigned char unk_0c;
};

class UnkType_10b76410
{
public:
    int Unk_10b76410(int Index);

private:
    unsigned char unk_00[0x1c];
    UnkType_10b76410_1c* unk_1c;
};

// UnkType_10b76410::Unk_10b76410
int UnkType_10b76410::Unk_10b76410(int Index)
{
    UnkType_10b76410_Entry* Entry = unk_1c->unk_04->Unk_10a0e220(unk_1c->unk_0c);
    UnkType_10b76410_Found* Found = Entry->unk_64->Unk_10a45b50();
    if ( Found && Found->unk_4a0 && Found->unk_400 )
    {
        int Result = 0;
        if ( Index < Found->unk_400->Unk_1099d840() )
        {
            Result = Found->unk_400->Unk_1099d870(Index);
        }
        return Result;
    }
    return 0;
}
