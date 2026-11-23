// campaign_leaf_4f0a40.cpp -- method at VA 0x10df0a40: stores its argument in the word at 0x0c when
// the function at VA 0x10d98f30 returns zero, else in that entry of the array at 0x08, and returns
// this object. The class and method names are invented; the offsets and the address are the
// binary's.

class UnkType_10df0a40
{
public:
    UnkType_10df0a40& Unk_10df0a40(const int& Value);

    int unk_00;
    int unk_04;
    int* unk_08;
    int unk_0c;
};

int Unk_10d98f30();

// UnkType_10df0a40::Unk_10df0a40
UnkType_10df0a40& UnkType_10df0a40::Unk_10df0a40(const int& Value)
{
    int Index = Unk_10d98f30();
    if ( Index == 0 )
    {
        unk_0c = Value;
    }
    else
    {
        unk_08[Index] = Value;
    }
    return *this;
}
