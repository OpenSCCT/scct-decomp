// campaign_leaf_2b1e10.cpp -- method at VA 0x10bb1e10 taking two arguments: looks the first up with
// the method at VA 0x10ba2e50 under flag 1 and then flag 0, and returns 1 as soon as the method at
// VA 0x10bad050 accepts the result found with the second argument; otherwise returns 0. The class
// and method names are invented; the addresses are the binary's.

class UnkType_10bb1e10
{
public:
    int Unk_10bb1e10(int First, int Second);
    void* Unk_10ba2e50(int Flag, int First);
    int Unk_10bad050(void* Found, int Flag, int Second);
};

// UnkType_10bb1e10::Unk_10bb1e10
int UnkType_10bb1e10::Unk_10bb1e10(int First, int Second)
{
    void* Found = Unk_10ba2e50(1, First);
    if ( Found && Unk_10bad050(Found, 1, Second) )
    {
        return 1;
    }
    Found = Unk_10ba2e50(0, First);
    if ( Found && Unk_10bad050(Found, 0, Second) )
    {
        return 1;
    }
    return 0;
}
