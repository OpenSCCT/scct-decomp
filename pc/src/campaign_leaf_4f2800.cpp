// campaign_leaf_4f2800.cpp -- method at VA 0x10df2800: returns the word at 0x0c when the function
// at VA 0x10d98f30 returns zero, else that entry of the array at 0x08. The class and method names
// are invented; the offsets and the address are the binary's.

class UnkType_10df2800
{
public:
    int Unk_10df2800();

    int unk_00;
    int unk_04;
    int* unk_08;
    int unk_0c;
};

int Unk_10d98f30();

// UnkType_10df2800::Unk_10df2800
int UnkType_10df2800::Unk_10df2800()
{
    int Index = Unk_10d98f30();
    return *( Index == 0 ? &unk_0c : &unk_08[Index] );
}
