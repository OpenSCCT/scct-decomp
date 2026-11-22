// campaign_leaf_095480.cpp -- one function at file offset 0x95480, preferred VA 0x10995480. It
// stores zero through its second and then its first pointer argument; the remaining seven
// arguments are not used. It has no this pointer. The class, method and parameter names are
// invented; the offset and the bytes are the binary's.

class UnkType_10995480
{
public:
    void UnkClearPair(int *First, int *Second, int Third, int Fourth, int Fifth, int Sixth,
                             int Seventh, int Eighth, int Ninth);
};

// UnkType_10995480::UnkClearPair
void UnkType_10995480::UnkClearPair(int *First, int *Second, int Third, int Fourth,
                                    int Fifth, int Sixth, int Seventh, int Eighth, int Ninth)
{
    *Second = 0;
    *First = 0;
}
