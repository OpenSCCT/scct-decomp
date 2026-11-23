// campaign_leaf_2640f0.cpp -- a member function at VA 0x10b640f0 taking an object and an array of
// ints: when both exist and the object's short at 0xa8 is a valid index into the array whose entry
// is between 1 and 254, it assigns an empty wide string to the string the array at 0x6c holds at
// that entry (with the member at VA 0x10907a00), passes the index and an empty wide string to the
// object's member at VA 0x10b59b30, clears the entry and sets the byte at 0x40. The class, method,
// member and parameter names are invented; the offsets, addresses and constants are the binary's.

class UnkType_10b640f0_String
{
public:
    void Unk_10907a00(const unsigned short* Text);

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b640f0_Owner
{
public:
    void Unk_10b59b30(int Index, const unsigned short* Text);

    unsigned char unk_00[0xa8];
    short unk_a8;
};

class UnkType_10b640f0_Array
{
public:
    int* unk_00;
    int unk_04;
};

class UnkType_10b640f0
{
public:
    void Unk_10b640f0(UnkType_10b640f0_Owner* Owner, UnkType_10b640f0_Array* Array);

private:
    unsigned char unk_00[0x40];
    bool unk_40;
    unsigned char unk_41[0x6c - 0x41];
    UnkType_10b640f0_String* unk_6c;
};

// UnkType_10b640f0::Unk_10b640f0
void UnkType_10b640f0::Unk_10b640f0(UnkType_10b640f0_Owner* Owner, UnkType_10b640f0_Array* Array)
{
    if ( Array && Owner )
    {
        int Index = Owner->unk_a8;
        if ( Index != -1 && Index >= 0 && Index < Array->unk_04 )
        {
            int Entry = Array->unk_00[Index];
            if ( Entry > 0 && Entry < 255 )
            {
                unk_6c[Entry].Unk_10907a00(L"");
                Owner->Unk_10b59b30(Index, L"");
                Array->unk_00[Index] = 0;
                unk_40 = true;
            }
        }
    }
}
