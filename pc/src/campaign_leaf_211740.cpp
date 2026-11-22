// campaign_leaf_211740.cpp -- a member function at VA 0x10b11740 that calls the free function at VA
// 0x10ea8b44 with its first argument, the result of the member at VA 0x10b11450 given its second
// argument, and its third argument. The class, method and parameter names are invented; the
// addresses are the binary's.

int Unk_10ea8b44(int First, int Second, int Third);

class UnkType_10b11740
{
public:
    int Unk_10b11450(int Value);
    void Unk_10b11740(int First, int Second, int Third);
};

// UnkType_10b11740::Unk_10b11740
void UnkType_10b11740::Unk_10b11740(int First, int Second, int Third)
{
    Unk_10ea8b44(First, Unk_10b11450(Second), Third);
}
