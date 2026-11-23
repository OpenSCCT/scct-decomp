// campaign_leaf_658570.cpp -- thiscall method at VA 0x10f58570 taking a list and three values: takes
// the list's count at 0x04 as an index and increments it, stores the result of the method at VA
// 0x10f582d0 (given the three values) at that index of the array at 0x10, then calls the method at
// VA 0x10f585d0 with the list when the index was zero, or the method at VA 0x10f58660 with the
// list's values at 0x08 and 0x0c and the third value otherwise. The class, method and member names
// are invented; the offsets and addresses are the binary's.

struct UnkType_10f58570_List
{
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int* unk_10;
};

class UnkType_10f58570
{
public:
    void Unk_10f58570(UnkType_10f58570_List* List, int First, int Second, int Third);
    int Unk_10f582d0(int First, int Second, int Third);
    void Unk_10f585d0(UnkType_10f58570_List* List);
    void Unk_10f58660(int First, int Second, int Third);
};

// UnkType_10f58570::Unk_10f58570
void UnkType_10f58570::Unk_10f58570(UnkType_10f58570_List* List, int First, int Second, int Third)
{
    int Index = List->unk_04++;

    List->unk_10[Index] = Unk_10f582d0(First, Second, Third);
    if ( Index == 0 )
    {
        Unk_10f585d0(List);
    }
    else
    {
        Unk_10f58660(List->unk_08, List->unk_0c, Third);
    }
}
