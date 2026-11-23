// campaign_leaf_4f0a70.cpp -- method at VA 0x10df0a70: returns the address of the word at 0x0c when
// the function at VA 0x10d98f30 returns zero, else of that entry of the array at 0x08. The class
// and method names are invented; the offsets and the address are the binary's.

class UnkType_10df0a70
{
public:
    int* Unk_10df0a70();

    int unk_00;
    int unk_04;
    int* unk_08;
    int unk_0c;
};

int Unk_10d98f30();

// UnkType_10df0a70::Unk_10df0a70
int* UnkType_10df0a70::Unk_10df0a70()
{
    int Index = Unk_10d98f30();
    if ( Index == 0 )
    {
        return &unk_0c;
    }
    return &unk_08[Index];
}
