// campaign_leaf_74fcd0.cpp -- free function at VA 0x1104fcd0: calls the method at VA 0x11056950 with its two
// arguments on the object returned by VA 0x11056900. All names are invented.

class UnkType_11056900
{
public:
    void Unk_11056950(int First, int Second);
};

UnkType_11056900* Unk_11056900();

// Unk_1104fcd0
void Unk_1104fcd0(int First, int Second)
{
    Unk_11056900()->Unk_11056950(First, Second);
}
