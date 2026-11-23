// campaign_leaf_74f920.cpp -- one function at file offset 0x74f920, preferred VA 0x1104f920. It
// passes its five arguments to the method at VA 0x11058600 of the object returned by the function
// at VA 0x11056900 (which returns the address of the global at VA 0x1132ea08). The type and
// function names are invented; the offset and the addresses are the binary's.

class UnkType_1104f920_Manager
{
public:
    void Unk_11058600(int First, int Second, int Third, int Fourth, int Fifth);
};

UnkType_1104f920_Manager* Unk_11056900();

// Unk_1104f920
void Unk_1104f920(int First, int Second, int Third, int Fourth, int Fifth)
{
    Unk_11056900()->Unk_11058600(First, Second, Third, Fourth, Fifth);
}
