// campaign_leaf_757190.cpp -- one function at file offset 0x757190, preferred VA 0x11057190. It
// asks the function at VA 0x11063530 to create an object from the third argument, the word the
// second points to and the fourth; on success it stores the object at 0xc of the record and
// returns 1. On failure, when the record's word at 0xc is set, it passes the local result to the
// function at VA 0x110634d0 and clears that word, and returns 0. The type and function names are
// invented; the offsets and the addresses are the binary's.

class UnkType_11057190_Object;

int Unk_11063530(UnkType_11057190_Object** Object, int Value, int Key, int Extra);
void Unk_110634d0(UnkType_11057190_Object** Object);

struct UnkType_11057190_Record
{
    unsigned char unk_0[0xc];
    UnkType_11057190_Object* unk_c;
};

// Unk_11057190
int __stdcall Unk_11057190(UnkType_11057190_Record* Record, int* Key, int Value, int Extra)
{
    UnkType_11057190_Object* Created;

    Created = 0;
    if ( Unk_11063530(&Created, Value, *Key, Extra) == 0 )
    {
        Record->unk_c = Created;
        return 1;
    }
    if ( Record->unk_c != 0 )
    {
        Unk_110634d0(&Created);
        Record->unk_c = 0;
    }
    return 0;
}
